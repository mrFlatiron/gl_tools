#include "common_volume.h"
#include <cmath>

common_volume::common_volume ()
{
  init_std ();
}

common_volume::~common_volume ()
{

}

float common_volume::left () const
{
  return m_x_min;
}

float common_volume::right () const
{
  return m_x_min + m_x_len;
}

float common_volume::bottom () const
{
  return m_y_min;
}

float common_volume::top () const
{
  return m_y_min + m_y_len;
}

float common_volume::near () const
{
  return -m_xy_ratio * 1.8;
}

float common_volume::far () const
{
  return m_xy_ratio * 1.8;
//  return 10;
}

float common_volume::xy_ratio () const
{
  return m_xy_ratio;
}

float common_volume::x_len () const
{
  return m_x_len;
}

float common_volume::y_len () const
{
  return m_y_len;
}

float common_volume::z_len () const
{
  return m_z_len;
}

void common_volume::set_by_len (const float x_len,
                                const float y_len)
{
  if (fabs (y_len) < 1e-7 || fabs (x_len) < 1e-7)
    {
      init_std ();
      return;
    }
  if (y_len > x_len)
    {
      m_x_min = -1;
      m_x_len = 2;
      m_xy_ratio = y_len / x_len;
      m_y_min = -m_xy_ratio;
      m_y_len = 2 * m_xy_ratio;
      m_z_min = -1;
      m_z_len = 2;
      return ;
    }
  m_y_min = -1;
  m_y_len = 2;
  m_xy_ratio = x_len / y_len;
  m_x_min = -m_xy_ratio;
  m_x_len = 2 * m_xy_ratio;
  m_z_min = -1;
  m_z_len = 2;
}


void common_volume::init_std ()
{
  m_x_min = -1;
  m_x_len = 2;
  m_y_min = -1;
  m_y_len = 2;
  m_xy_ratio = 1;
  m_z_min = -1;
  m_z_len = 2;
}
