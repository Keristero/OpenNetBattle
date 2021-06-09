#pragma once
#ifdef BN_MOD_SUPPORT

#include <sol/sol.hpp>
#include "../bnPlayer.h"
#include "../bnPlayerState.h"
#include "../bnTextureType.h"
#include "../bnChargeEffectSceneNode.h"
#include "../bnAnimationComponent.h"
#include "../bnAI.h"
#include "../bnPlayerControlledState.h"
#include "../bnPlayerIdleState.h"
#include "../bnPlayerHitState.h"

/*! \brief scriptable navi
 *
 * Uses callback functions defined in an external file to configure
 */

class ScriptedPlayer : public Player {
  sol::state& script;
  float height{};
public:
  friend class PlayerControlledState;
  friend class PlayerIdleState;

  ScriptedPlayer(sol::state& script);

  void SetChargePosition(const float x, const float y);
  void SetFullyChargeColor(const sf::Color& color);
  void SetHeight(const float height);
  void SetAnimation(const std::string& path);
  const float GetHeight() const;
  Animation& GetAnimationObject();
  Battle::Tile* GetCurrentTile() const;

  CardAction* OnExecuteSpecialAction() override final;
  CardAction* OnExecuteBusterAction() override final;
  CardAction* OnExecuteChargedBusterAction() override final;
};

#endif