#pragma once
#include "bnCardAction.h"
#include "bnAnimation.h"
#include <SFML/Graphics.hpp>

class SpriteProxyNode;
class Character;

class AirHockeyCardAction : public CardAction {
private:
  sf::Sprite overlay;
  SpriteProxyNode* attachment{ nullptr };
  Animation attachmentAnim;
  int damage;
public:
  AirHockeyCardAction(Character& owner, int damage);
  ~AirHockeyCardAction();
  void Update(double _elapsed) override;
  void OnAnimationEnd();
  void OnEndAction();
  void OnExecute();
};