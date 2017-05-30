#ifndef CAMERA_HELPER_H
#define CAMERA_HELPER_H


class camera_helper
{
private:
  float m_oxy_angle;
  float m_ozy_angle;
  float m_zoom_coef;
public:
  camera_helper ();
  ~camera_helper ();
  float oxy_angle () const;
  float ozy_angle () const;
  float zoom () const;
  void rotate_oxy (const float delta);
  void rotate_ozy (const float delta);
  void zoom_in ();
  void zoom_out ();
  void nice_init ();
};

#endif // CAMERA_HELPER_H
