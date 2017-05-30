#include "gl_handler.h"
#include <GL/gl.h>

gl_handler::gl_handler ()
{
  m_modelview.setToIdentity ();
}

gl_handler::~gl_handler ()
{

}

std::array<float, 6> gl_handler::compute_bounds (const float *vertices, const int vertex_count)
{
  float x_min, x_max, y_min, y_max, z_min, z_max;
  std::array<float, 6> retval;
  if (vertex_count < 1)
    return retval;
  x_min = vertices[0];
  x_max = x_min;
  y_min = vertices[1];
  y_max = y_min;
  z_min = vertices[2];
  z_max = z_min;
  for (int i = 1; i < vertex_count; i++)
    {
      int k = 3 * i;
      x_min = (vertices[k] < x_min) ? vertices[k] : x_min;
      x_max = (vertices[k] > x_max) ? vertices[k] : x_max;
      y_min = (vertices[k + 1] < y_min) ? vertices[k + 1] : y_min;
      y_max = (vertices[k + 1] > y_max) ? vertices[k + 1] : y_max;
      z_min = (vertices[k + 2] < z_min) ? vertices[k + 2] : z_min;
      z_max = (vertices[k + 2] > z_max) ? vertices[k + 2] : z_max;
    }
  retval[0] = x_min;
  retval[1] = x_max;
  retval[2] = y_min;
  retval[3] = y_max;
  retval[4] = z_min;
  retval[5] = z_max;
  return retval;
}

void gl_handler::verify_bounds (std::array<float, 6> &bounds)
{
  for (int i = 0; i < 3; i++)
    {
      float c_min = bounds[2 * i];
      float c_max = bounds[2 * i + 1];
      float c_len = c_max - c_min;
      if (fabs (c_len) < 1e-7)
        {
          if (fabs (c_min) < 1e-7)
            {
              c_min = -1e-7;
              c_max = 1e-7;
            }
          else
            {
              c_max += 0.1f * c_max;
              c_min -= 0.1f * c_max;
            }
        }
      bounds[2 * i] = c_min;
      bounds[2 * i + 1] = c_max;
    }
}

void gl_handler::to_common_volume (std::array<float, 6> &bounds)
{
  verify_bounds (bounds);

  float x_min = bounds[0];
  float x_max = bounds[1];
  float y_min = bounds[2];
  float y_max = bounds[3];
  float z_min = bounds[4];
  float z_max = bounds[5];

  m_common_volume.set_by_len (x_max - x_min, y_max - y_min);

  QMatrix4x4 translator (1, 0, 0, -(x_max + x_min) / 2,
                         0, 1, 0, -(y_max + y_min) / 2,
                         0, 0, 1, -(z_max + z_min) / 2,
                         0, 0, 0, 1);

  m_modelview.scale (m_common_volume.x_len () / (x_max - x_min),
                     m_common_volume.y_len () / (y_max - y_min),
                     m_common_volume.z_len () / (z_max - z_min));

  m_modelview *= translator;
}

void gl_handler::to_common_volume (const float *vertices, const int vertex_count)
{
  std::array<float, 6> bounds = compute_bounds (vertices, vertex_count);

  to_common_volume (bounds);

}

void gl_handler::to_common_volume (const float x_min,
                                   const float x_max,
                                   const float y_min,
                                   const float y_max,
                                   const float z_min,
                                   const float z_max)
{
  std::array<float, 6> bounds;
  bounds[0] = x_min;
  bounds[1] = x_max;
  bounds[2] = y_min;
  bounds[3] = y_max;
  bounds[4] = z_min;
  bounds[5] = z_max;

  to_common_volume (bounds);
}

void gl_handler::apply_camera ()
{
  QMatrix4x4 rotator;
  rotator.setToIdentity ();
  rotator.rotate (180. / M_PI * m_camera.ozy_angle (), 1, 0, 0);
  rotator.rotate (180. / M_PI * m_camera.oxy_angle (), 0, 0, 1);


  rotator *= m_modelview;
  m_modelview = rotator;
}

void gl_handler::set_modelview_identity ()
{
  m_modelview.setToIdentity ();
}

inline void glMultMatrix (const float *ptr) {glMultMatrixf (ptr);}
inline void glMultMatrix (const double *ptr) {glMultMatrixd (ptr);}

void gl_handler::gl_set_modelview () const
{
  glMatrixMode (GL_MODELVIEW);
  glLoadIdentity ();
  glMultMatrix (m_modelview.constData ());
}

void gl_handler::gl_set_ortho (const float xy_ratio) const
{
  glMatrixMode (GL_PROJECTION);
  glLoadIdentity ();

  float xy_side = m_common_volume.xy_ratio () * m_camera.zoom ();
  glOrtho (-xy_side * xy_ratio, xy_side * xy_ratio,
           -xy_side, xy_side,
            m_common_volume.near (),
           m_common_volume.far ());
}

camera_helper &gl_handler::camera ()
{
  return m_camera;
}
