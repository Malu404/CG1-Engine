#ifndef CAMERA_H
#define CAMERA_H

#include <SDL_render.h>
#include "scene.h"
#include "ray.h"
#include "light.h"
#include "shapes/shape.h"

class Camera {
    public:
        Vec3 pos, bg_color;
        Camera () : pos(Vec3()), bg_color(Vec3(1.0, 1.0, 1.0)), viewport(Viewport()) {}
        Camera (Vec3 pos, double width, double height, double cols, double rows, double viewport_distance, Vec3 bg_color, Vec3 ambient_light) :
            pos(pos), bg_color(bg_color), viewport(Viewport(Vec3(pos.x, pos.y, pos.z - viewport_distance), width, height, cols, rows)) {}

        void draw_scene(SDL_Renderer* renderer, Scene scene) {
            SDL_SetRenderDrawColor(renderer, static_cast<Uint8>(bg_color.x), static_cast<Uint8>(bg_color.y), static_cast<Uint8>(bg_color.z), 255);
            SDL_RenderClear(renderer);
            Light light = scene.lights.front();
            for (Shape* s : scene.objects) {
                
                for (int row = 0; row < viewport.rows; row++) {
                    for (int col = 0; col < viewport.cols; col++ ) {
                        Vec3 dr = ((viewport.p00 + viewport.dx * col - viewport.dy * row) - pos).normalize();
                        Ray r = Ray(pos, dr);

                        auto [intersects, t1, t2] = s->intersects(r);
                        if (intersects && (t1 > 0.0 || t2 > 0.0)) {
                            double min_t = ((t2 < 0.0) || (t1 < t2)) ? t1 : t2;
                            Vec3 p_intersect = r.at(min_t);
                            Vec3 l = (light.pos - p_intersect).normalize(); // vetor apontando na direção da luz
                            Vec3 n = s->get_normal(p_intersect);
                            Vec3 r = (2.0 * (l.dot(n)))*n - l; // vetor l refletido na normal

                            double nl = n.dot(l);
                            double rl = r.dot(l);
                            if (nl < 0.0) { nl = 0.0; rl = 0.0; }
                            if (rl < 0.0) { rl = 0.0; }

                            Vec3 iamb = s->mat.k_ambient * scene.ambient_light * s->mat.color;
                            Vec3 idif = s->mat.k_diffuse * nl * s->mat.color * light.color;
                            Vec3 iesp = s->mat.k_specular * pow(rl, s->mat.e) * light.color;

                            Vec3 ieye = iamb + idif + iesp;

                            draw_pixel(renderer, col, row, ieye.clamp(0.0, 1.0).rgb_255());
                        }
                    }
                }

            }
            SDL_RenderPresent(renderer);
        }
    
    private:
        inline void draw_pixel(SDL_Renderer* renderer, int x, int y, Vec3 color) {
            SDL_SetRenderDrawColor(renderer, static_cast<Uint8>(color.x), static_cast<Uint8>(color.y), static_cast<Uint8>(color.z), 255);
            SDL_RenderDrawPoint(renderer, x, y);
        }

        class Viewport {
        public:
            Vec3 pos, dx, dy, top_left, p00;
            double width, height;
            int cols, rows;
            
            Viewport () {
                Vec3 pos = Vec3(0.0, 0.0, -1.0);
                double width = 1.0; double height = 1.0;
                double cols = 256; double rows = 256;

                Vec3 dx = Vec3(width/cols, 0.0, 0.0);
                Vec3 dy = Vec3(0.0, height/cols, 0.0);
                Vec3 top_left = Vec3(pos.x - width/2.0, pos.y + height/2.0, pos.z);
                Vec3 p00 = top_left + dx/2 - dy/2;

                this->pos = pos; this->dx = dx; this->dy = dy; this->top_left = top_left; this->p00 = p00;
                this->width = width; this->height = height;
                this->cols = cols; this->rows = rows;
            }

            Viewport (Vec3 pos, double width, double height, double cols, double rows) {
                Vec3 dx = Vec3(width/cols, 0.0, 0.0);
                Vec3 dy = Vec3(0.0, height/rows, 0.0);
                Vec3 top_left = Vec3(pos.x - width/2.0, pos.y + height/2.0, pos.z);
                Vec3 p00 = top_left + dx/2 - dy/2;

                this->pos = pos; this->dx = dx; this->dy = dy; this->top_left = top_left; this->p00 = p00;
                this->width = width; this->height = height;
                this->cols = cols; this->rows = rows;      
            }
        };
        Viewport viewport;
};

#endif