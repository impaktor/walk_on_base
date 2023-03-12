#include "Camera.h"

Camera::Camera(SDL_Rect rect, const TiledMap *map): m_map{map}{
  camera = rect;

  const int y_max_map = m_map->mHeight;
  const int x_max_map = m_map->mWidth;

  // Map corners to screen coordinates. Regardless of map
  // projection, we know map corners will be min/max position
  m_x_min_screen = m_map->get_screen_pos(vec{0,         y_max_map}).x;
  m_x_max_screen = m_map->get_screen_pos(vec{x_max_map, 0}).x;
  m_y_min_screen = m_map->get_screen_pos(vec{0,         0}).y;
  m_y_max_screen = m_map->get_screen_pos(vec{x_max_map, y_max_map}).y;
}


void Camera::set(vec pos){

  //Center the camera over the player, regardless of map projection
  vec screen_pos = m_map->get_screen_pos(pos);
  camera.x = (screen_pos.x + m_map->mTileWidth  / 2) - camera.w / 2;
  camera.y = (screen_pos.y + m_map->mTileHeight / 2) - camera.h / 2;

    //Keep the camera in bounds
  if(camera.x < m_x_min_screen)
    camera.x = m_x_min_screen;
  if(camera.y < m_y_min_screen)
    camera.y = m_y_min_screen;
  if(camera.x + camera.w > m_x_max_screen)
    camera.x = m_x_max_screen - camera.w;
  if(camera.y + camera.h > m_y_max_screen)
    camera.y = m_y_max_screen - camera.h;

  if(ImGui::Begin("camera##1")){
    std::ostringstream ss, s1, s2, s3;
    ss << "x_min: " << m_x_min_screen << " x_max: " << m_x_max_screen;
    ImGui::Text("%s", ss.str().c_str());
    s1 << "y_min: " << m_y_min_screen << " y_max: " << m_y_max_screen;
    ImGui::Text("%s", s1.str().c_str());

    s2 << "camera: " << vec{camera.x, camera.y} << " : c.w=" << camera.w << " c.h=" << camera.h;
    ImGui::Text("%s", s2.str().c_str());

    s3 << "screen pos: " << screen_pos;
    ImGui::Text("%s", s3.str().c_str());
  }
  ImGui::End();
}
