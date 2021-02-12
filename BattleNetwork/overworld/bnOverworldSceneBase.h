#pragma once

#include <SFML/Graphics.hpp>
#include <time.h>
#include <future>
#include <Swoosh/Activity.h>
#include <Swoosh/ActivityController.h>

#include "../bnScene.h"
#include "../bnMenuWidget.h"
#include "../bnCamera.h"
#include "../bnInputManager.h"
#include "../bnAudioResourceManager.h"
#include "../bnShaderResourceManager.h"
#include "../bnTextureResourceManager.h"
#include "../bnNaviRegistration.h"
#include "../bnPA.h"
#include "../bnDrawWindow.h"
#include "../bnAnimation.h"
#include "../bnCardFolderCollection.h"
#include "../bnAnimatedTextBox.h"

// overworld
#include "bnOverworldActor.h"
#include "bnOverworldPlayerController.h"
#include "bnOverworldPathController.h"
#include "bnOverworldTeleportController.h"
#include "bnOverworldMap.h"
#include "bnEmotes.h"

class Background; // forward decl

namespace Overworld {
  class SceneBase : public Scene {
  private:
    struct WorldSprite {
      std::shared_ptr<SpriteProxyNode> node;
      int layer{ 0 };
    };

    std::shared_ptr<Actor> playerActor;
    Overworld::EmoteWidget emote;
    Overworld::EmoteNode emoteNode;
    Overworld::TeleportController teleportController{};
    Overworld::PlayerController playerController{};
    Overworld::QuadTree quadTree{};
    std::vector<Overworld::Actor> npcs;
    std::vector<Overworld::PathController> pathControllers{};

    Camera camera; /*!< camera in scene follows player */
    bool clicked{ false }, scaledmap{ false };
    // Selection input delays
    double maxSelectInputCooldown; /*!< Maximum delay */
    double selectInputCooldown; /*!< timer to allow key presses again */
    bool extendedHold{ false };

    sf::Vector2f returnPoint{};
    bool teleportedOut{ false }; /*!< We may return to this area*/

    // menu widget
    MenuWidget menuWidget;

    SpriteProxyNode webAccountIcon; /*!< Status icon if connected to web server*/
    Animation webAccountAnimator; /*!< Use animator to represent different statuses */
    bool lastIsConnectedState; /*!< Set different animations if the connection has changed */

    // Bunch of sprites and their attachments
    Background* bg{ nullptr }; /*!< Background image pointer */
    Overworld::Map map; /*!< Overworld map */
    std::vector<WorldSprite> sprites;

    AnimatedTextBox textbox;

    double animElapsed{};

    /*!< Current navi selection index */
    SelectedNavi currentNavi{},
      lastSelectedNavi{ std::numeric_limits<SelectedNavi>::max() };

    bool gotoNextScene{ false }; /*!< If true, player cannot interact with screen yet */
    bool guestAccount{ false };

    CardFolderCollection folders; /*!< Collection of folders */
    PA programAdvance;

    std::future<WebAccounts::AccountState> accountCommandResponse; /*!< Response object that will wait for data from web server*/

    /**
    * @brief aux function clears the map object
    */
    void ClearMap(unsigned rows, unsigned cols);

    std::shared_ptr<Map::Tileset> ParseTileset(unsigned int firstgid, const std::string& data);
    void LoadBackground(const std::string& value);
    void DrawMap(sf::RenderTarget& target, sf::RenderStates states);
    void DrawTiles(sf::RenderTarget& target, sf::RenderStates states);
    void DrawSprites(sf::RenderTarget& target, sf::RenderStates states) const;

#ifdef __ANDROID__
    void StartupTouchControls();
    void ShutdownTouchControls();
#endif

  protected:
    virtual std::string GetText(const std::string& path);
    virtual std::shared_ptr<sf::Texture> GetTexture(const std::string& path);
    virtual std::shared_ptr<sf::SoundBuffer> GetAudio(const std::string& path);

  public:

    SceneBase() = delete;
    SceneBase(const SceneBase&) = delete;

    /**
     * @brief Loads the player's library data and loads graphics
     */
    SceneBase(swoosh::ActivityController&, bool guestAccount);

    /**
     * @brief Checks input events and listens for select buttons. Segues to new screens.
     * @param elapsed in seconds
     */
    virtual void onUpdate(double elapsed) override;

    /**
     * @brief Draws the UI
     * @param surface
     */
    virtual void onDraw(sf::RenderTexture& surface) override;

    /**
     * @brief Stops music, plays new track, reset the camera
     */
    virtual void onStart() override;

    /**
     * @brief Does nothing
     */
    virtual void onLeave() override;

    /**
     * @brief Does nothing
     */
    virtual void onExit() override;

    /**
     * @brief Checks the selected navi if changed and loads the new images
     */
    virtual void onEnter() override;

    /**
     * @brief Resets the camera
     */
    virtual void onResume() override;

    /**
     * @brief Stops the music
     */
    virtual void onEnd() override;

    /**
    * @brief Update's the player sprites according to the most recent selection
    */
    void RefreshNaviSprite();

    /**
    * @brief Equip a folder for the navi that was last used when playing as them
    */
    void NaviEquipSelectedFolder();

    /**
    * @brief Effectively sets the scene
    */
    void LoadMap(const std::string& data);

    void TeleportUponReturn(const sf::Vector2f& position);
    const bool HasTeleportedAway() const;

    void SetBackground(Background*);

    /**
     * @brief Add a sprite
     * @param _sprite
     */
    void AddSprite(std::shared_ptr<SpriteProxyNode> _sprite, int layer);

    /**
     * @brief Remove a sprite
     * @param _sprite
     */
    void RemoveSprite(const std::shared_ptr<SpriteProxyNode> _sprite);

    //
    // Menu selection callbacks
    //

    void GotoChipFolder();
    void GotoNaviSelect();
    void GotoConfig();
    void GotoMobSelect();
    void GotoPVP();

    //
    // Getters
    //

    Overworld::QuadTree& GetQuadTree();
    Camera& GetCamera();
    Map& GetMap();
    std::shared_ptr<Actor> GetPlayer();
    PlayerController& GetPlayerController();
    TeleportController& GetTeleportController();
    SelectedNavi& GetCurrentNavi();
    Background* GetBackground();
    AnimatedTextBox& GetTextBox();

    //
    // Optional events that can be decorated further
    //
    virtual void OnEmoteSelected(Emotes emote);

    //
    // Required implementations
    //
    virtual void OnTileCollision() = 0;
    std::pair<unsigned, unsigned> PixelToRowCol(const sf::Vector2i& px, const sf::RenderWindow& window) const;
  };
}