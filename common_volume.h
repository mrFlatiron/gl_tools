#ifndef COMMON_VOLUME_H
#define COMMON_VOLUME_H


class common_volume
{
private:
  float m_x_min;
  float m_x_len;
  float m_y_min;
  float m_y_len;
  float m_xy_ratio; //  max (x / y, y / x)
  float m_z_min;
  float m_z_len;
public:
  common_volume ();
  ~common_volume ();
  float left () const;
  float right () const;
  float bottom () const;
  float top () const;
  float near () const;
  float far () const;
  float xy_ratio () const;
  float x_len () const;
  float y_len () const;
  float z_len () const;
  void set_by_len (const float x_len,
                   const float y_len);

private:
  void init_std ();

};

#endif // COMMON_VOLUME_H
