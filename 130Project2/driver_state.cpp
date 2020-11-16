#include "driver_state.h"
#include <cstring>

driver_state::driver_state()
{
}

driver_state::~driver_state()
{
    delete [] image_color;
    delete [] image_depth;
}

// This function should allocate and initialize the arrays that store color and
// depth.  This is not done during the constructor since the width and height
// are not known when this class is constructed.
void initialize_render(driver_state& state, int width, int height)
{
    std::cout << "enter initialize_render" << std::endl;
    state.image_width=width;
    state.image_height=height;
    state.image_color=0;
    state.image_depth=0;
    pixel* p = new pixel[width * height];
    for (int i = 0; i < width * height; i++) {
        p[i] = make_pixel(0, 0, 0);
    }
    
    std::cout<<"TODO: allocate and initialize state.image_color and state.image_depth."<<std::endl;
    std::cout << "leave initialize_render" << std::endl;
}

// This function will be called to render the data that has been stored in this class.
// Valid values of type are:
//   render_type::triangle - Each group of three vertices corresponds to a triangle.
//   render_type::indexed -  Each group of three indices in index_data corresponds
//                           to a triangle.  These numbers are indices into vertex_data.
//   render_type::fan -      The vertices are to be interpreted as a triangle fan.
//   render_type::strip -    The vertices are to be interpreted as a triangle strip.
void render(driver_state& state, render_type type)
{
    std::cout << "enter render" << std::endl;
    data_geometry* dg = new data_geometry[state.num_vertices];
    for (int i = 0; i < state.num_vertices; i++) {
        dg[i].data = new float;
    }
    data_vertex* dv=new data_vertex[state.num_vertices] ;
    for (int i = 0; i < state.num_vertices; i++) {
        dv[i].data = &state.vertex_data[i];
        state.vertex_shader(dv[i], dg[i], state.uniform_data);
    }
    for (int i = 0; i < state.num_vertices; i += 3) {
        if(i+2<state.num_vertices)
            rasterize_triangle(state, dg[i], dg[i + 1], dg[i + 2]);
    }

    std::cout<<"TODO: implement rendering."<<std::endl;
    std::cout << "leave render" << std::endl;
}


// This function clips a triangle (defined by the three vertices in the "in" array).
// It will be called recursively, once for each clipping face (face=0, 1, ..., 5) to
// clip against each of the clipping faces in turn.  When face=6, clip_triangle should
// simply pass the call on to rasterize_triangle.
void clip_triangle(driver_state& state, const data_geometry& v0,
    const data_geometry& v1, const data_geometry& v2,int face)
{
    std::cout << "enter clip_triangle" << std::endl;
    if(face==6)
    {
        rasterize_triangle(state, v0, v1, v2);
        return;
    }
    std::cout<<"TODO: implement clipping. (The current code passes the triangle through without clipping them.)"<<std::endl;
    clip_triangle(state,v0,v1,v2,face+1);
    std::cout << "leave clip_triangle" << std::endl;
}

float areaCal(int axi,int ayi,int bxi, int byi,int cxi,int cyi) {
    float ax = axi;
    float ay = ayi;
    float bx = bxi;
    float by = byi;
    float cx = cxi;
    float cy = cyi;
    float area = 0.5 * ((float)(bx * (float)cy - (float)cx * by) + (float)(cx * ay - (float)ax * cy) + (float)(ax * by - (float)bx * ay));
    return area;
}

// Rasterize the triangle defined by the three vertices in the "in" array.  This
// function is responsible for rasterization, interpolation of data to
// fragments, calling the fragment shader, and z-buffering.
void rasterize_triangle(driver_state& state, const data_geometry& v0,
    const data_geometry& v1, const data_geometry& v2)
{
    std::cout << "enter rasterize_triangle" << std:: endl;
    vec4 v0Position=v0.gl_Position / v0.gl_Position.x[3];
    vec4 v1Position = v1.gl_Position / v1.gl_Position.x[3];
    vec4 v2Position = v2.gl_Position / v2.gl_Position.x[3];
    int ax = ((v0Position.x[0] + 1) / 2) * state.image_width;
    int ay = ((v0Position.x[1] + 1) / 2) * state.image_height;
    int bx = ((v1Position.x[0] + 1) / 2) * state.image_width;
    int by = ((v1Position.x[1] + 1) / 2) * state.image_height;
    int cx = ((v0Position.x[0] + 1) / 2) * state.image_width;
    int cy = ((v0Position.x[1] + 1) / 2) * state.image_height;
    float abc = areaCal(ax,ay,bx,by,cx,cy);
    for (int i = 0; i < state.image_width * state.image_height; i++) {
        int px = i % state.image_width;
        int py = state.image_height - i / state.image_width-1;
        float pbc = areaCal(px, py, bx, by, cx, cy);
        float pac = areaCal(px, py, ax, ay, cx, cy);
        float pab = areaCal(px, py, ax, ay, bx, by);
        float alpha = pbc / abc;
        float beta = pac / abc;
        float gama = pab / abc;
        //if (alpha >= 0 && beta >= 0 && gama >= 0) {
        //    state.vertex_data[i * state.floats_per_vertex + (state.floats_per_vertex - 3)] = 255;
        //    state.vertex_data[i * state.floats_per_vertex + (state.floats_per_vertex - 2)] = 255;
        //    state.vertex_data[i * state.floats_per_vertex + (state.floats_per_vertex - 1)] = 255;
        //}
        //else {
        //    state.vertex_data[i * state.floats_per_vertex + (state.floats_per_vertex - 3)] = 0;
        //    state.vertex_data[i * state.floats_per_vertex + (state.floats_per_vertex - 2)] = 0;
        //    state.vertex_data[i * state.floats_per_vertex + (state.floats_per_vertex - 1)] = 0;
        //}
    }
    std::cout<<"TODO: implement rasterization"<<std::endl;
    std::cout << "leave rasterize_triangle" << std::endl;
}

