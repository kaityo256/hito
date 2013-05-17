#include "colors.inc"
camera{
  location<30,30,-80>
  look_at<30,30,0>
}
light_source{
  <40,40,-40>
  color 1.2*White
}
plane{
  <0,0,1>,1
  pigment{checker color White color Gray scale 2.0}
}
plane{
  <0,1,0>,-3
  pigment{checker color White color Gray scale 2.0}
}
