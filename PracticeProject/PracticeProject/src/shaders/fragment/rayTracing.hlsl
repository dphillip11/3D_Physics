#version 330 core
out vec4 fragColor;


uniform float iTime;
uniform float cam_y;
uniform vec3 iResolution;
uniform vec3 iMouse = vec3(0, 0, 0);
uniform float cam_depth = 0.5f;

struct cylinder
{
    vec3 centre;
    vec3 axis;
    float length;
    float radius;
};

struct Box
{
    vec3 centre;
    vec3 size;
};

#define SMOOTHING 4
float jitter[40] = float[40](0.4739, 0.3905, -0.2918, -0.3103, 0.2716, 0.1766, 0.0919, 0.4453, -0.1357, -0.2515, -0.1222, 0.1569,
    -0.2444, 0.0942, 0.0114, 0.1858, 0.3087, 0.3564, 0.3435, 0.1275, -0.3936, -0.2622, 0.2247, -0.4922, -0.1987, 0.3452, 0.2421, 0.1636, -0.3001,
    0.4931, 0.0106, -0.1659, -0.2407, -0.4106, 0.2318, 0.4340, -0.4474, 0.4919, -0.1978, 0.1289);

//////////////////////objects

//collider ID's
const int NO_COL = -2;
const int GROUND = -1;
const int BALL[5] = int[5](0, 1, 2, 3, 4);
const int BASE = 5;
const int FRAME = 6;
const int PIPEJOINT = 7;
const int STRINGS = 8;


cylinder frame[8] = cylinder[8](
    //frame
    cylinder(vec3(0., 8., 8.), vec3(1, 0, 0), 10., 0.25),
    cylinder(vec3(0., 8., 2.), vec3(1, 0, 0), 10., 0.25),
    cylinder(vec3(-5, 8., 5.), vec3(0, 0, 1), 6., 0.25),
    cylinder(vec3(5, 8., 5.), vec3(0, 0, 1), 6., 0.25),
    //legs
    cylinder(vec3(-5, 4., 2.), vec3(0, 1, 0), 8., 0.25),
    cylinder(vec3(-5, 4., 8.), vec3(0, 1, 0), 8., 0.25),
    cylinder(vec3(5, 4., 2.), vec3(0, 1, 0), 8., 0.25),
    cylinder(vec3(5, 4., 8.), vec3(0, 1, 0), 8., 0.25));

cylinder strings[10];

vec4 balls[5] = vec4[5](
    //balls
    vec4(-4., 2, 5, 1),
    vec4(-2, 2, 5, 1),
    vec4(0., 2, 5, 1),
    vec4(2, 2, 5, 1),
    vec4(4, 2, 5, 1));

vec4 pipeJoints[4] = vec4[4](
    //pipe joints
    vec4(-5, 8, 2, 0.25),
    vec4(5, 8, 2, 0.25),
    vec4(-5, 8, 8, 0.25),
    vec4(5, 8, 8, 0.25));

Box base = Box(vec3(0, 0.25, 5), vec3(11.25, 0.5, 7));

vec3 ballColor[5] = vec3[5](vec3(1, 0, 0), vec3(0, 1, 0), vec3(0, 0, 0), vec3(0, 0, 1), vec3(1, 1, 0));
vec3 frameColor = vec3(0.3, 0.3, 0.3);
vec3 groundColor = vec3(0.2, 0.2, 0.8);
vec3 skyColor = vec3(0.5, 0.8, 1);
vec3 stringColor = vec3(0.4, 0.4, 0.4);
vec3 baseColor = vec3(214., 141., 6.) / 255.;


struct Camera
{
    vec3 pos;
    vec3 target;
    float depth;
    vec3 up;
    vec3 right;
    vec3 forward;
};


Camera cam = Camera(vec3(1), vec3(0, 5, 3), 0.7, vec3(0, 1, 0), vec3(1, 0, 0), vec3(0, 0, 1));

vec3 light_pos;
float reflectionDenominator = 150.;
float shininess_ball = 128.;
float shininess_frame = 90.;
float shininess_base = 32.;
float shininess_ground = 16.;
float shininess_string = 5.;

float ambientIntensity = 0.3;



struct intersection {
    int collider;
    vec3 normal;
    float distance;
};

void GetGroundIntersection(vec3 ray_origin, vec3 ray_dir, inout intersection intx)
{
    //check intersection with ground, y=0
    if (ray_origin.y > 0. && ray_dir.y < 0.)
    {
        float d = abs(ray_origin.y / ray_dir.y);

        if (d > 0. && (intx.collider == NO_COL || d < intx.distance))
        {
            intx.collider = GROUND;
            intx.distance = d;
            intx.normal = vec3(0, 1, 0);
        }
    }
}

void GetSphereIntersection(vec3 ray_origin, vec3 ray_dir, vec4 sphere, inout intersection intx, int ID)
{
    //vector to sphere directly
    vec3 sphere_dir = sphere.xyz - ray_origin;
    //calculate projection along ray direction
    float dotP = dot(sphere_dir, ray_dir);
    //ignore spheres in opposite direction
    if (dotP < 0.)
        return;
    vec3 ray_proj = dotP * ray_dir;
    float ray_length = length(ray_proj);
    vec3 ray_point = ray_proj + ray_origin;
    //distance from line to centre
    float d = length(sphere.xyz - ray_point);
    if (d > sphere.w)
        return;
    //calculate sphere intersection, pythagoras
    float overlap = sqrt(pow(sphere.w, 2.) - pow(d, 2.));
    ray_length -= overlap;
    if (ray_length < intx.distance || intx.collider == NO_COL)
    {
        intx.distance = ray_length;
        intx.collider = ID;
        intx.normal = normalize(ray_origin + ray_length * ray_dir - sphere.xyz);
    }
}

void WorldSphereIntersections(vec3 ray_origin, vec3 ray_dir, inout intersection intx)
{
    for (int i = 0; i < balls.length(); i++)
    {
        GetSphereIntersection(ray_origin, ray_dir, balls[i], intx, BALL[i]);
    }
    for (int i = 0; i < pipeJoints.length(); i++)
    {
        GetSphereIntersection(ray_origin, ray_dir, pipeJoints[i], intx, PIPEJOINT);
    }
}

void GetBoxIntersection(vec3 ray_origin, vec3 ray_dir, Box box, inout intersection intx, int ID)
{
    vec3 m = 1.0 / ray_dir;
    vec3 n = m * (ray_origin - box.centre);
    vec3 k = abs(m) * 0.5 * box.size;
    vec3 t1 = -n - k;
    vec3 t2 = -n + k;

    float tN = max(max(t1.x, t1.y), t1.z);
    float tF = min(min(t2.x, t2.y), t2.z);

    if (tN > tF || tF < 0.0)
        return;

    vec3 oN = -sign(ray_dir) * step(t1.yzx, t1.xyz) * step(t1.zxy, t1.xyz);

    if (tN > 0. && tN < intx.distance)
    {
        intx.distance = tN;
        intx.normal = oN;
        intx.collider = ID;
    }

}

void WorldBoxIntersections(vec3 ray_origin, vec3 ray_dir, inout intersection intx)
{
    GetBoxIntersection(ray_origin, ray_dir, base, intx, BASE);
}

void GetCylinderIntersection(vec3 ray_origin, vec3 ray_dir, cylinder cyl, inout intersection intx, int ID)
{
    vec3 A = cyl.centre - cyl.axis * (cyl.length * 0.5);
    vec3 OA = ray_origin - A;
    float a = dot(ray_dir, ray_dir) - pow(dot(ray_dir, cyl.axis), 2.);
    float b = 2. * (dot(ray_dir, OA) - dot(ray_dir, cyl.axis) * dot(OA, cyl.axis));
    float c = dot(OA, OA) - pow(dot(OA, cyl.axis), 2.) - pow(cyl.radius, 2.);

    float det = b * b - 4. * a * c;
    if (det < 0.)
        return;
    float t1 = (-b + sqrt(det)) / (2. * a);
    float t2 = (-b - sqrt(det)) / (2. * a);
    float distance = min(t1, t2);
    vec3 t = ray_origin + distance * ray_dir;
    vec3 At = t - A;
    float axisPos = dot(At, cyl.axis);
    if (axisPos > cyl.length || axisPos < 0.)
        return;

    if (distance >= 0. && (distance < intx.distance || intx.collider == NO_COL))
    {
        intx.collider = ID;
        intx.distance = distance;
        vec3 point = ray_origin + ray_dir * distance;
        vec3 c2p = point - cyl.centre;
        vec3 normal = c2p - dot(c2p, cyl.axis) * cyl.axis;
        intx.normal = normalize(normal);
    }
}

void WorldCylinderIntersections(vec3 ray_origin, vec3 ray_dir, inout intersection intx)
{
    for (int i = 0; i < frame.length(); i++)
    {
        GetCylinderIntersection(ray_origin, ray_dir, frame[i], intx, FRAME);
    }
    for (int i = 0; i < strings.length(); i++)
    {
        GetCylinderIntersection(ray_origin, ray_dir, strings[i], intx, STRINGS);
    }
}

intersection GetIntersection(vec3 ray_origin, vec3 ray_dir)
{
    intersection intx = intersection(NO_COL, vec3(0), 0.);

    GetGroundIntersection(ray_origin, ray_dir, intx);

    WorldSphereIntersections(ray_origin, ray_dir, intx);

    WorldBoxIntersections(ray_origin, ray_dir, intx);

    WorldCylinderIntersections(ray_origin, ray_dir, intx);

    return intx;

}

float GetLocalDiffuse(vec3 point, vec3 normal, vec3 ray_dir)
{
    vec3 light_dir = normalize(light_pos - point);
    //check if light is obstructed
    intersection incomingLight = GetIntersection(point, light_dir);
    float obstructedModifier = 1.;
    if (incomingLight.collider != NO_COL)
        obstructedModifier = 0.4;
    //calculate diffuse value
    float diffuseIntensity = 0.6 * max(dot(light_dir, normal), 0.);
    return diffuseIntensity * obstructedModifier + ambientIntensity;
}

vec3 GetReflectedColor(vec3 point, vec3 normal, vec3 ray_direction)
{
    vec3 reflectDir = normalize(reflect(ray_direction, normal));
    vec3 light_dir = normalize(light_pos - point);

    //check for reflected objects
    intersection reflectedLight = GetIntersection(point, reflectDir);
    vec3  reflectedColor;

    if (reflectedLight.collider == NO_COL)
    {
        reflectedColor = skyColor;
    }
    else if (reflectedLight.collider == GROUND)
    {
        reflectedColor = groundColor;
    }
    else if (reflectedLight.collider < BASE)
    {
        reflectedColor = ballColor[BALL[reflectedLight.collider]];
    }
    else if (reflectedLight.collider == BASE)
    {
        reflectedColor = baseColor;
    }
    else if (reflectedLight.collider == FRAME || reflectedLight.collider == PIPEJOINT)
    {
        reflectedColor = frameColor;
    }
    else if (reflectedLight.collider == STRINGS)
    {
        reflectedColor = stringColor;
    }

    vec3 rPoint = point + reflectDir * reflectedLight.distance;
    vec3 rNormal = reflectedLight.normal;
    float reflectedBrightness = GetLocalDiffuse(rPoint, rNormal, reflectDir);

    return reflectedColor * reflectedBrightness;
}

vec3 GetColor(vec3 ray_origin, vec3 ray_direction)
{
    intersection collision = GetIntersection(ray_origin, ray_direction);
    //apply sky for non hit
    if (collision.collider == NO_COL)
        return (0.3 + abs(ray_direction.z)) * skyColor;
    //get point of collision
    vec3 point = ray_origin + ray_direction * collision.distance;
    vec3 normal = collision.normal;

    vec3 materialColor;
    float reflectivity;
    float shininess;

    if (collision.collider == GROUND)
    {
        materialColor = groundColor;
        shininess = shininess_ground;
    }
    else if (collision.collider == FRAME || collision.collider == PIPEJOINT)
    {
        materialColor = frameColor;
        shininess = shininess_frame;
    }
    else if (collision.collider < BASE)
    {
        materialColor = ballColor[BALL[collision.collider]];
        shininess = shininess_frame;
    }
    else if (collision.collider == BASE)
    {
        materialColor = baseColor;
        shininess = shininess_frame;
    }
    else if (collision.collider == STRINGS)
    {
        materialColor = stringColor;;
        shininess = shininess_string;
    }
    reflectivity = shininess / reflectionDenominator;
    //diffuse
    vec3 diffuseColor = GetLocalDiffuse(point, normal, ray_direction) * materialColor;
    //reflected
    vec3 reflectedColor = GetReflectedColor(point, normal, ray_direction);
    //specular
    vec3 reflectDir = normalize(reflect(ray_direction, normal));
    vec3 light_dir = normalize(light_pos - point);
    vec3 spec = pow(max(dot(light_dir, reflectDir), 0.), shininess) * vec3(1);

    return diffuseColor + (reflectedColor + spec) * reflectivity;

}


void PositionBalls()
{
    float angle = 0.3 * sin(iTime * 3.);
    //vertical and hoirizonatl components of rotated line
    float xD1 = 6. * max(sin(angle), 0.);
    float xD2 = 6. * min(sin(angle), 0.);
    float yD1 = 6. - (6. * cos(min(angle, 0.)));
    float yD2 = 6. - (6. * cos(max(angle, 0.)));
    float xDiffs[5] = float[5](xD2, 0.3 * xD2, 0., 0.3 * xD1, xD1);
    float yDiffs[5] = float[5](yD1, 0.3 * yD1, 0., 0.3 * yD2, yD2);
    vec3 spacing = vec3(2, 0, 0);
    //string length coefficient
    float sC = 5. / 6.;

    vec3 topPos1 = vec3(-4., 7.75, 8.);
    vec3 topPos2 = vec3(-4., 7.75, 2.);

    for (int i = 0; i < balls.length(); i++)
    {
        balls[i].xyz = vec3(-4. + xDiffs[i] + spacing.x * float(i), 2. + yDiffs[i], 5.);

        //calculate string positions

        vec3 bottomPos = vec3(-4. + 2. * float(i) + xDiffs[i] * sC, 3. + yDiffs[i] * sC, 5.);
        vec3 position1 = (topPos1 + bottomPos) * 0.5;
        vec3 axis1 = normalize(topPos1 - bottomPos);
        vec3 position2 = (topPos2 + bottomPos) * 0.5;
        vec3 axis2 = normalize(topPos2 - bottomPos);

        strings[2 * i] = cylinder(position1, axis1, 6., 0.02);
        strings[2 * i + 1] = cylinder(position2, axis2, 6., 0.02);

        topPos1 += spacing;
        topPos2 += spacing;
    }

}


vec3 GetRayDir(vec2 uv)
{
    vec3 rayScreenIntersection = vec3(cam.pos + uv.x * cam.right + uv.y * cam.up + cam.depth * cam.forward);
    vec3 rayDir = normalize(rayScreenIntersection - cam.pos);
    return rayDir;
}


vec3 SmoothColor(vec2 uv, int n)
{
    n = min(n, 20);
    vec3 totalColor;
    vec3 rayDir = GetRayDir(uv);
    vec3 color = GetColor(cam.pos, rayDir);
    totalColor += color;
    //antialiasing, resamples neighbouring pixels and averages, performance heavy
    for (int i = 0; i < n; i++)
    {
        vec3 rayDir = GetRayDir(uv + vec2(jitter[2 * i], jitter[2 * i + 1]) / iResolution.y);
        color = GetColor(cam.pos, rayDir);
        totalColor += color;
    }
    color = totalColor / float(n + 1);
    return color;
}


void main()
{
    light_pos = cam.target + vec3(10. * sin(iMouse.x / 100.), 12. , 15. * cos(iMouse.x / 100.));
    PositionBalls();

    // Normalized pixel coordinates (from -1 to 1)
    vec2 uv = (gl_FragCoord.xy - 0.5 * iResolution.xy) / iResolution.y;

    cam.pos = vec3(15. * sin(iTime / 10.), 10., 5. + 15. * cos(iTime / 10.));
    cam.depth = cam_depth;
    cam.pos.y = cam_y;
    //align with camera
    cam.forward = normalize(cam.target - cam.pos);
    cam.right = normalize(cross(vec3(0., 1., 0.), cam.forward));
    cam.up = normalize(cross(cam.forward, cam.right));


    vec3 color = SmoothColor(uv, SMOOTHING);

    // Output to screen
    fragColor = vec4(color, 01);
}