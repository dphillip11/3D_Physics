#version 330 core
out vec4 fragColor;

#define MAX_RANGE 1000.
#define SPHERES_N 5

uniform float iTime;
uniform float cam_y;
uniform vec3 iResolution;
uniform vec3 iMouse = vec3(0, 0, 0);
uniform sampler2D marble;
uniform float cam_depth = 0.5f;

vec4 spheres[5] = vec4[5](vec4(-4., 2, 5, 1), vec4(-2, 2, 5, 1), vec4(0., 2, 5, 1), vec4(2, 2, 5, 1), vec4(4, 2, 5, 1));
vec3 colors[5] = vec3[5](vec3(1, 0, 0), vec3(0, 1, 0), vec3(0, 0, 0), vec3(0, 0, 1), vec3(1, 1, 0));
vec3 groundColor = vec3(0.2, 0.2, 0.8);
vec3 skyColor = vec3(0.5, 0.8, 1);
vec3 light_pos ;
vec3 cam_pos;
//regulates perspective
float ambientIntensity = 0.2;

/*collider ID 
- 2     none
 -1     ground,
 0+     sphereIndex
 */

struct contactPoint {
    int collider;
    float distance;
};

contactPoint getIntersection(vec3 ray_origin, vec3 ray_direction)
{
    //set non collision condition
    contactPoint collision = contactPoint(-2, MAX_RANGE);

    //check intersection with ground, y=0
    if (ray_origin.y > 0. && ray_direction.y < 0.)
    {
        float dist_to_ground = abs(ray_origin.y / ray_direction.y);
        collision.distance = min(collision.distance, dist_to_ground);
        collision.collider = -1;
    }

    //check sphere intersections
    for (int i = 0; i < SPHERES_N; i++)
    {
        //vector to sphere directly
        vec3 sphere_dir = spheres[i].xyz - ray_origin;
        //calculate projection along ray direction
        float dotP = dot(sphere_dir, ray_direction);
        //ignore spheres in opposite direction
        if (dotP < 0.)
            continue;
        vec3 ray_proj = dotP * ray_direction;
        float ray_length = length(ray_proj);
        vec3 ray_point = ray_proj + ray_origin;
        float distance_to_sphere = length(spheres[i].xyz - ray_point);
        if (distance_to_sphere < spheres[i].w)
        {
            if (ray_length < collision.distance)
            {
                //calculate sphere intersection, pythagoras
                float overlap = sqrt(pow(spheres[i].w, 2.) - pow(distance_to_sphere, 2.));
                collision.collider = i;
                collision.distance = ray_length - overlap;
            }
        }
    }
    return collision;

}

vec3 GetNormal(int collider, vec3 point)
{
    if (collider == -1)
        return vec3(0, 1, 0);
    return normalize(point - spheres[collider].xyz);
}

float GetLocalDiffuse(vec3 point, vec3 normal, vec3 ray_direction)
{
    vec3 light_dir = normalize(light_pos - point);
    //check if light is obstructed
    contactPoint incomingLight = getIntersection(point, light_dir);
    float obstructedModifier = 1.;
    if (incomingLight.collider != -2)
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
    contactPoint reflectedLight = getIntersection(point, reflectDir);
    vec3  reflectedColor;
    if (reflectedLight.collider == -2)
        //specular calculation
        return pow(max(dot(light_dir, reflectDir), 0.), 32.) * skyColor;
    else if (reflectedLight.collider == -1)
    {
        reflectedColor = texture(marble, point.xz / 40. + vec2(0.5,0.5)).rgb;
    }
    else
    {
        reflectedColor = colors[reflectedLight.collider];
    }

    vec3 rPoint = point + reflectDir * reflectedLight.distance;
    vec3 rNormal = GetNormal(reflectedLight.collider, rPoint);
    float reflectedBrightness = GetLocalDiffuse(rPoint, rNormal, reflectDir);

    return reflectedColor * reflectedBrightness;
}






vec3 GetColor(vec3 ray_origin, vec3 ray_direction)
{
    contactPoint collision = getIntersection(ray_origin, ray_direction);
    //apply sky for non hit
    if (collision.collider == -2)
        return (0.3 + abs(ray_direction.z)) * skyColor;
    //get point of collision
    vec3 point = ray_origin + ray_direction * collision.distance;
    vec3 normal = GetNormal(collision.collider, point);
    vec3 materialColor;

    if (collision.collider == -1)
    {
        materialColor = texture(marble, point.xz / 40. + vec2(0.5, 0.5)).rgb;;
    }
    else
    {
        materialColor = colors[collision.collider];
    }

    //diffuse
    vec3 diffuseColor = GetLocalDiffuse(point, normal, ray_direction) * materialColor;
    //reflected
    vec3 reflectedColor = GetReflectedColor(point, normal, ray_direction);
    if (collision.collider == -1)
        return diffuseColor + reflectedColor * 0.2;
    return diffuseColor + reflectedColor;


}


void main()
{
    spheres[0].x = -4. - max(0., 2. * sin(iTime));
    spheres[0].y = 2. + max(0., 2. * sin(iTime));
    spheres[4].x = 4. - min(0., 2. * sin(iTime));
    spheres[4].y = 2. - min(0., 2. * sin(iTime));

    light_pos = vec3((iMouse.x - iResolution.x / 2.) / 10., 10., (iMouse.y - iResolution.y / 2.) / 5. + 10.);
    // Normalized pixel coordinates (from -1 to 1)
    vec2 uv = (gl_FragCoord.xy - 0.5 * iResolution.xy) / iResolution.y;
    cam_pos = vec3(10. * sin(iTime / 20.), cam_y, 5. + 10. * cos(iTime / 20.));
    //cam_pos = vec3(0., 20.,-10.);

    //align with camera
    vec3 cam_forward = normalize(spheres[2].xyz - cam_pos);
    vec3 cam_right = normalize(cross(vec3(0., 1., 0.), cam_forward));
    vec3 cam_up = normalize(cross(cam_forward, cam_right));

    vec3 rayScreenIntersection = vec3(cam_pos + uv.x * cam_right + uv.y * cam_up + cam_depth * cam_forward);


    vec3 rayDir = normalize(rayScreenIntersection - cam_pos);
    vec3 color = GetColor(cam_pos, rayDir);


    // Output to screen
    fragColor = vec4(color, 1.0);
}