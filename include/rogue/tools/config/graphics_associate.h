#ifndef INCLUDE_ROGUE_TOOLS_CONFIG_GRAPHICS_ASSOCIATE_H_
#define INCLUDE_ROGUE_TOOLS_CONFIG_GRAPHICS_ASSOCIATE_H_

#include <map>
class GraphicsAssociate {
  bool sprite = false;

 public:
  void Default() {
    sprite = false;
    associates_.clear();
    associates_['m'] = 'm';
    associates_['g'] = 'g';
    associates_['j'] = 'j';
    associates_['b'] = 'b';
    associates_['E'] = 'E';
    associates_['#'] = '#';
    associates_['.'] = '.';
    associates_['@'] = '@';
    associates_['<'] = '<';
    associates_['>'] = '>';
    associates_['+'] = '+';
    associates_['$'] = '$';
    associates_['t'] = 't';
  }
  void Sprite() {
    sprite = true;
    associates_.clear();
    associates_['m'] = 0xE000;
    associates_['g'] = 0xE001;
    associates_['j'] = 0xE002;
    associates_['b'] = 0xE003;
    associates_['E'] = 0xE004;
    associates_['#'] = 0xE005;
    associates_['.'] = 0xE006;
    associates_['@'] = 0xE007;
    associates_['<'] = 0xE008;
    associates_['>'] = 0xE009;
    associates_['+'] = 0xE010;
    associates_['$'] = 0xE011;
    associates_['t'] = 0xE015;
  }
  int Get(int key) {
    return associates_[key];
  }
  bool StateOnSprite() {
    return sprite;
  }
  std::map<int, int> associates_;
};

#endif  // INCLUDE_ROGUE_TOOLS_CONFIG_GRAPHICS_ASSOCIATE_H_
