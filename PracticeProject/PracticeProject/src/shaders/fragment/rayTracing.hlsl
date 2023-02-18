#version 330 core
out vec4 fragColor;

#define MAX_RANGE 40.
#define SPHERES_N 4

uniform float iTime;
uniform vec3 iResolution;

vec4 spheres[4] = vec4[4](vec4(-3,2,5,1), vec4(-1,2,5,1), vec4(1,2,5,1), vec4(3,2,5,1));
vec3 colors[4] = vec3[4](vec3(1,0,0),vec3(0,1,0),vec3(0,0,1),vec3(1,1,0));
vec3 groundColor = vec3(0.2, 0.2, 0.8);
vec3 light_pos = vec3(0.,10.,3);
vec3 cam_pos = vec3(0,4.,-0.5);

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
        if (dotP < 0)
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
                float overlap = sqrt(pow(spheres[i].w, 2) - pow(distance_to_sphere, 2));
                collision.collider = i;
                collision.distance = ray_length - overlap;
            }
        }
    }
    return collision;

}
vec3 GetColor(vec3 ray_origin, vec3 ray_direction)
{
    contactPoint collision = getIntersection(ray_origin, ray_direction);
    //apply sky for non hit
    if (collision.collider == - 2)
        return ray_direction.z * vec3(0.5, 0.8, 1);

    //get point of collision
    vec3 point = ray_origin + ray_direction * collision.distance;
    //check for light
    vec3 light_dir = normalize(light_pos - point);

    contactPoint incomingLight = getIntersection(point, light_dir);
    //apply diffuse modifier
    float diffuseModifier = 1.;
    //check for obstructions
    if (incomingLight.collider != -2)
        diffuseModifier = 0.4;


    if (collision.collider == -1)
    {
        vec3 normal = vec3(0, 1, 0);
        vec3 reflectDir = reflect(-ray_direction, normal);
        vec3 point = ray_origin + (collision.distance * ray_direction);
        float diffuseIntensity = 0.6 * max(dot(light_dir, normal),0);
        float specularIntensity = 0.5 * max(dot(light_dir, reflectDir), 0);
        return groundColor * (diffuseIntensity * diffuseModifier + specularIntensity + 0.1);
    }
        

    vec3 normal = normalize(point - spheres[collision.collider].xyz);
    vec3 reflectDir = reflect(-ray_direction, normal);
    light_dir = normalize(light_pos - point);
    float diffuseIntensity = 0.6 * max(dot(light_dir, normal), 0);
    float specularIntensity = 0.5 * max(dot(light_dir, reflectDir), 0);
    return (diffuseIntensity * diffuseModifier + specularIntensity) * colors[collision.collider];
        
        
}



void main()
{
    spheres[0].x = -3. -max(0.,2. * sin(iTime));
    spheres[0].y = 2 + max(0.,2. *sin(iTime));
    spheres[3].x = 3. - min(0.,2. *sin(iTime));
    spheres[3].y = 2 - min(0.,2. *sin(iTime));
    
    
    // Normalized pixel coordinates (from -1 to 1)
    vec2 uv = (2. * gl_FragCoord.xy/iResolution.xy)-1.;
    //align with camera
    uv = uv + vec2(cam_pos.x,cam_pos.y);
    vec3 rayDir = normalize(vec3(uv.xy,0) - cam_pos);
    vec3 color = GetColor(cam_pos, rayDir);


    // Output to screen
    fragColor = vec4(color,1.0);
}