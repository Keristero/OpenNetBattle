#include "bnObstacle.h"
#include "bnTextureResourceManager.h"
#include "bnShaderResourceManager.h"

Obstacle::Obstacle(Field* _field, Team _team) : Spell(_field, _team)  {
  this->field = _field;
  this->team = _team;

  SetFloatShoe(true);
  SetLayer(1);
  markTile = false;
  hitboxProperties.flags = Hit::none;
}

Obstacle::~Obstacle() {

}

bool Obstacle::CanMoveTo(Battle::Tile * next)
{
  return (Entity::CanMoveTo(next));
}

void Obstacle::AdoptTile(Battle::Tile * tile)
{
  this->Spell::AdoptTile(tile); // favor spell grouping
}

void Obstacle::OnUpdate(float _elapsed) {
}

