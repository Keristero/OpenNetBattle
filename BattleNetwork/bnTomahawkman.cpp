#include "bnTomahawkman.h"

#include "bnField.h"
#include "bnTextureResourceManager.h"
#include "bnAudioResourceManager.h"
#include "bnDrawWindow.h"
#include "bnLogger.h"
#include "bnBusterCardAction.h"
#include "bnTomahawkSwingCardAction.h"
#include <Swoosh/Ease.h>

const float COPY_DROP_COOLDOWN = 0.15f; // in seconds

const std::string RESOURCE_PATH = "resources/navis/tomahawk/tomahawk.animation";

CardAction* Tomahawkman::OnExecuteBusterAction()
{
  return new BusterCardAction(*this, false, 1*GetAttackLevel());
}

CardAction* Tomahawkman::OnExecuteChargedBusterAction()
{
  return new BusterCardAction(*this, true, 10*GetAttackLevel());
}

CardAction* Tomahawkman::OnExecuteSpecialAction() {
  return new TomahawkSwingCardAction(*this, 10*GetAttackLevel() + 10);
}

Tomahawkman::Tomahawkman() : Player()
{
  chargeEffect.setPosition(0, -20.0f);
  SetName("Tomahawkman");
  SetLayer(0);
  team = Team::red;
  SetElement(Element::none);

  animationComponent->SetPath(RESOURCE_PATH);
  animationComponent->Reload();

  setTexture(Textures().LoadTextureFromFile("resources/navis/tomahawk/navi_tomahawk_atlas.png"));

  SetHealth(1000);

  chargeEffect.SetFullyChargedColor(sf::Color::Green);
}

Tomahawkman::~Tomahawkman()
{
}

const float Tomahawkman::GetHeight() const
{
  ;
  return 100.0f;
}

void Tomahawkman::OnUpdate(float _elapsed)
{
  // Continue with the parent class routine
  Player::OnUpdate(_elapsed);
}

void Tomahawkman::OnDelete()
{
  Player::OnDelete();
}
