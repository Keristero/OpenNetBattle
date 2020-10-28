#pragma once
#include "bnCardAction.h"
#include "bnAnimation.h"
#include <SFML/Graphics.hpp>

class SpriteProxyNode;
class Character;

class SwordCardAction : public CardAction {
protected:
  SpriteProxyNode* blade;
  SpriteProxyNode* hilt;
  Animation bladeAnim, hiltAnim;
  int damage;
  Element element;
public:
  SwordCardAction(Character* owner, int damage);
  virtual ~SwordCardAction();
  void OnUpdate(float _elapsed);
  void OnAnimationEnd() override;
  void EndAction();
  void Execute();
  virtual void OnSpawnHitbox();
  void SetElement(Element elem);
  const Element GetElement() const;
};

