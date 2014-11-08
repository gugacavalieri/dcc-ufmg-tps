/*
 * rendering.h
 *
 */

#ifndef RENDERING_RENDERING_H_
#define RENDERING_RENDERING_H_

#define DEFAULT_WIDTH 800
#define DEFAULT_HEIGHT 600

/* rendering methods */
void init_rendering(int argc, char **argv);
void processArguments(int argc, char **argv);
void render_scene();
void register_callbacks();



#endif /* RENDERING_RENDERING_H_ */