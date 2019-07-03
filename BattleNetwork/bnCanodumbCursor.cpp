#include "bnCanodumbCursor.h"
#include "bnTextureResourceManager.h"
#include "bnAudioResourceManager.h"
#include "bnField.h"

using sf::IntRect;

#define MAX_COOLDOWN_1 0.5f
#define MAX_COOLDOWN_2 0.25f
#define MAX_COOLDOWN_3 0.175f

#define RESOURCE_PATH "resources/mobs/canodumb/canodumb.animation"

CanodumbCursor::CanodumbCursor(Field* _field, Team _team, Canodumb* _parent) : Artifact(_field) {
  SetFloatShoe(true);

  animationComponent = new AnimationComponent(this);
  this->RegisterComponent(animationComponent);

  parent = _parent;
  target = parent->GetTarget();

  SetLayer(0);
  direction = Direction::LEFT;

  setTexture(*TEXTURES.GetTexture(TextureType::MOB_CANODUMB_ATLAS));
  setScale(2.f, 2.f);

  //Components setup and load
  animationComponent->Setup(RESOURCE_PATH);
  animationComponent->Load();
  animationComponent->SetAnimation(MOB_CANODUMB_CURSOR);
  animationComponent->OnUpdate(0);

  switch (parent->GetRank()) {
  case Canodumb::Rank::_1:
    maxcooldown = MAX_COOLDOWN_1;
    break;
  case Canodumb::Rank::_2:
    maxcooldown = MAX_COOLDOWN_2;
    break;
  case Canodumb::Rank::_3:
    maxcooldown = MAX_COOLDOWN_3;
    break;
  }

  movecooldown = maxcooldown;
}

void CanodumbCursor::OnUpdate(float _elapsed) {
  setPosition(tile->getPosition().x, tile->getPosition().y);

  movecooldown -= _elapsed;

  if (movecooldown <= 0) {
    if (this->GetTile() == target->GetTile() && !target->IsPassthrough()) {
      this->Delete();

      parent->ChangeState<CanodumbAttackState>();
    }
    else {
      movecooldown = maxcooldown;

      Field* f = this->GetField();
      Battle::Tile* t = f->GetAt(this->GetTile()->GetX() - 1, this->GetTile()->GetY());

      if (t != nullptr) {
        this->GetTile()->RemoveEntityByID(this->GetID());
        t->AddEntity(*this);
      }
      else {
        this->Delete();
      }
    }
  }
}

CanodumbCursor::~CanodumbCursor()
{
}
