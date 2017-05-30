#ifndef GL_HANDLER_H
#define GL_HANDLER_H

#include <QMatrix4x4>
#include <array>

#include "common_volume.h"
#include "camera_helper.h"

class gl_handler
{
private:
  QMatrix4x4 m_modelview;
  common_volume m_common_volume;
  camera_helper m_camera;
public:
  gl_handler ();
  ~gl_handler ();

  void to_common_volume (const float *vertices, const int vertex_count);
  void to_common_volume (const float x_min,
                         const float x_max,
                         const float y_min,
                         const float y_max,
                         const float z_min,
                         const float z_max);
  void apply_camera ();
  void set_modelview_identity ();
  void gl_set_modelview () const;
  void gl_set_ortho (const float xy_ratio = 1) const;
  camera_helper &camera ();
private:
  static std::array<float, 6> compute_bounds (const float *vertices, const int vertex_count);
  static void verify_bounds (std::array<float, 6> &bounds);
  void to_common_volume (std::array<float, 6> &bounds);
};

#endif // GL_HANDLER_H
