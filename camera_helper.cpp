#include "camera_helper.h"
#include <cmath>

camera_helper::camera_helper ()
{
  m_oxy_angle = 0;
  m_ozy_angle = 0;
  m_zoom_coef = 1;
}

camera_helper::~camera_helper ()
{

}

float camera_helper::oxy_angle () const
{
  return m_oxy_angle;
}

float camera_helper::ozy_angle () const
{
  return m_ozy_angle;
}

float camera_helper::zoom () const
{
  return m_zoom_coef;
}

void camera_helper::rotate_oxy (const float delta)
{
  m_oxy_angle = fmod (m_oxy_angle + delta, 2 * M_PI);
}

void camera_helper::rotate_ozy (const float delta)
{
  m_ozy_angle = fmod (m_ozy_angle + delta, 2 * M_PI);
}

void camera_helper::zoom_in ()
{
  m_zoom_coef /= 1.05f;
}

void camera_helper::zoom_out ()
{
  m_zoom_coef *= 1.05f;
}

void camera_helper::nice_init ()
{
  m_ozy_angle = -1.14f;
  m_oxy_angle = -2.11f;
  m_zoom_coef = 2.0f;
}
