//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include <string>
#include "oktypes.h"
#include "GameLogic.h"
#include "GameType.h"
#include "GameSequence.h"
#include <src/Engine/network/GameSave.h>
#include <src/Engine/network/UDPPeerConnection.h>

class Logger;

#include "src/Utility/AssetData.h"
#include "src/Utility/ArrayList.h"
#include "src/Utility/HashMap.h"
#include "src/Utility/audio/Sound.h"
#include "src/Utility/ControlsManager.h"
#include "src/Utility/OKMenu.h"
#include "../Engine/Engine.h"
#include "../Engine/nd/NDGameEngine.h"

#include "CustomGameEditor.h"
#include "GameSequenceEditor.h"

//#include "Stats/GameStats.h"
#include "Stats/UserStatsForSpecificGameAndDifficulty.h"
#include "Stats/LeaderBoardAndHighScoreBoardEntry.h"
//#include "GameTestMenu.h"

class OKGameGameStats;

class GameTestMenuControl;
//class Engine;
//class NDGameEngine;
class Logger;
class ControlsManager;
class SpriteManager;
class AudioManager;
class PreloadedSprite;
class OKFont;
class CaptionManager;
class Room;


//=========================================================================================================================
class OKGame : public NDGameEngine, public std::enable_shared_from_this<OKGame>
{//=========================================================================================================================
private:
	typedef NDGameEngine super;
public:
	static Logger log;

protected:
	bool bgShaderFBOTextureToggle = false;

public:

	//static sp<OKGame> b;
	sp<Sound>music = nullptr;
	sp<OKTexture> keyboardTexture = nullptr;
	sp<OKTexture> controllerTexture = nullptr;
	sp<OKTexture> controllerIconTexture = nullptr;
	sp<OKTexture> keyboardIconTexture = nullptr;
	sp<OKTexture> onlineTexture = nullptr;
	sp<OKTexture> networkIconTexture = nullptr;
	sp<OKTexture> gearsTexture = nullptr;
	sp<OKTexture> chartTexture = nullptr;

	static sp<OKTexture> upperLeft;
	static sp<OKTexture> top;
	static sp<OKTexture> upperRight;
	static sp<OKTexture> left;
	static sp<OKTexture> right;
	static sp<OKTexture> lowerLeft;
	static sp<OKTexture> bottom;
	static sp<OKTexture> lowerRight;

	sp<GameLogic> getPlayer1Game();
	sp<PuzzlePlayer> getPlayer1();
	void setOKGameFBOSize();
	void renderGameIntoFBO(sp<GameLogic> g, bool useColorFilter);
	void drawOKGameFBO(float x0, float x1, float y0, float y1);
	virtual void render() override;

	OKGame();
	OKGame(ND* nD);
	virtual ~OKGame() override;
	virtual void init() override;



	void initPlayer();
	bool isMultiplayer();
	
	//long long randomSeed = -1;
	//sp<GameType> originalSettings = nullptr;
	long long timeRenderBegan = 0;

	virtual bool isNetworkGame() override;
	void debugKeys();
	virtual void update() override;

	
	int shaderCount = rand() % GLUtils::bgShaderCount;
	void changeBG();
	virtual void shakeSmall() override;
	virtual void shakeHard() override;
	

	static sp<Sprite> bobsGameLogoSmall;

	void initAssets();
	sp<Sprite> getSpriteFromName(const string& name);
	//sp<OKGame> getThis();

	virtual void updateControls() override;
	virtual void resetPressedButtons() override;
	virtual void setButtonStates() override;

	sp<vector<sp<PuzzlePlayer>>>players;
	

	

	//-----------------
	//menus
	//-----------------

		
	sp<Caption> pressEnterToRestartCaption = nullptr;

	virtual void setupMenus() override;
	virtual bool renderMenus() override;
	virtual bool updateMenus() override;

	bool startScreenMenuShowing = false;
	sp<OKMenu>startScreenMenu = nullptr;
	sp<OKMenu>infoMenu = nullptr;
	sp<OKMenu>patreonMenu = nullptr;
	sp<OKMenu>forumMenu = nullptr;
	sp<OKMenu>activityMenu = nullptr;
	int startScreenMenuCursorPosition = 0;
	void startScreenMenuUpdate();
	void startScreenMenuRender();


	static sp<vector<string>>activityStream;
	bool sentActivityStreamRequest = false;
	//bool gotActivityStream = false;
	//long long lastCheckedActivityResponseTime = 0;

	sp<OKMenu>gettingGamesFromServerMenu = nullptr;
	void gettingGamesFromServerMenuUpdate();
	void gettingGamesFromServerMenuRender();
	bool gettingGamesFromServerMenuShowing = false;
	long long gettingGamesFromServerDotsTime = 0;
	int gettingGamesFromServerCount = 0;

	string cycleDots(int tries);

	virtual void updateTitleScreenLogo() override;
	virtual void updateTitleMenuLogoTexture() override;
	virtual void titleMenuUpdate() override;
	virtual void titleMenuRender() override;

	//sp<Caption> pressEnterCaption = nullptr;

	virtual void pauseMenuUpdate() override;
	virtual void pauseMenuRender() override;
	long long timeLastChangedSetting = 0;
	long long timeStartedChangedSetting = 0;

	void difficultyMenuUpdate();
	//void difficultyMenuRender();
	bool difficultyMenuShowing = false;
	sp<OKMenu>difficultyMenu = nullptr;
	int difficultyMenuCursorPosition = 0;

	void controllerMenuUpdate();
	void controllerMenuRender();
	bool controllerMenuShowing = false;
	sp<OKMenu>controllerMenu = nullptr;
	int controllerMenuCursorPosition = 0;
	bool controllerMenuTestingButtons = false;

	void localMultiplayerPlayerJoinMenuUpdate();
	void localMultiplayerPlayerJoinMenuRender();
	bool localMultiplayerPlayerJoinMenuShowing = false;
	sp<OKMenu>localMultiplayerPlayerJoinMenu = nullptr;
	int localMultiplayerPlayerJoinMenuCursorPosition = 0;
	sp<Caption> localMultiplayerPressStartCaption = nullptr;

	void playerDifficultyMiniMenuUpdate(sp<PuzzlePlayer>p);
	void playerDifficultyMiniMenuRender(sp<PuzzlePlayer>p, float x, float y);

	void playerControllerSettingsMenuInit(sp<OKMenu> m, sp<PuzzlePlayer>p);
	void playerControllerSettingsMenuToggle(sp<OKMenu> m, sp<PuzzlePlayer>p);
	void playerSettingsMenuInit(sp<OKMenu> m, sp<PuzzlePlayer>p);
	void playerSettingsMenuLeft(sp<OKMenu> m, sp<PuzzlePlayer>p);
	void playerSettingsMenuRight(sp<OKMenu> m, sp<PuzzlePlayer>p);
	void playerPauseMiniMenuUpdate(sp<PuzzlePlayer>p);
	void playerPauseMiniMenuRender(sp<PuzzlePlayer>p, float x0, float x1, float y0, float y1);

	void loginMenuUpdate();
	void loginMenuRender();
	bool loginMenuShowing = false;
	sp<OKMenu>loginMenu = nullptr;
	int loginMenuCursorPosition = 0;
	bool textStarted = false;
	string saveRoomConfigNameText = "";
	string userNameOrEmailText = "";
	string userNameText = "";
	string emailText = "";
	//bool showPasswordStars = false;
	string passwordText = "";
	string passwordStarsText = "";
	string confirmPasswordText = "";
	string confirmPasswordStarsText = "";
	bool stayLoggedIn = true;

	sp<Caption> errorLabel = nullptr;
	sp<Caption> statusLabel = nullptr;

	//bool loggedIn = false;

	void createAccountMenuUpdate();
	void createAccountMenuRender();
	bool createAccountMenuShowing = false;
	int lastMX = 0;
	int lastMY = 0;
	sp<OKMenu>createAccountMenu = nullptr;
	int createAccountMenuCursorPosition = 0;
	
	sp<vector<sp<Room>>>rooms;
	sp<Room> currentRoom = nullptr;

	void addToRoomsMenu(sp<Room> c, string name, string id);
	void populateRoomsMenu();
	void networkMultiplayerLobbyMenuUpdate();
	void networkMultiplayerLobbyMenuRender();
	void selectGameSequenceOrSingleGameTypeFilterMenuUpdate();
	void selectGameSequenceFilterMenuUpdate();
	void selectSingleGameTypeFilterMenuUpdate();
	bool networkMultiplayerLobbyMenuShowing = false;
	bool selectGameSequenceFilterMenuShowing = false;
	bool selectSingleGameTypeFilterMenuShowing = false;
	bool selectGameSequenceOrSingleGameTypeFilterMenuShowing = false;
	//sp<vector<sp<Caption>>>*hostingFriendCaptions = ms<vector><sp<Caption>>();
	//sp<vector<sp<Caption>>>*playingFriendCaptions = ms<vector><sp<Caption>>();
	//int hostingFriendsCursorPosition = 0;
	sp<OKMenu>networkMultiplayerLobbyMenu = nullptr;
	sp<OKMenu>yourStatsMenu = nullptr;
	sp<OKMenu>leaderBoardMenu = nullptr;
	sp<OKMenu>roomsMenu = nullptr;
	sp<OKMenu>friendsOnlineMenu = nullptr;
	//sp<Caption>onlineFriendsLabel = nullptr;
	int networkMultiplayerLobbyMenuCursorPosition = 0;
	bool selectingHostedGame = false;
	//sp<UDPPeerConnection>hostPeer = nullptr;
	sp<vector<sp<UDPPeerConnection>>>joinedPeers;// = ms<vector><sp<UDPPeerConnection>>();
	bool hostStartedGame = false;
	string friendUserName = "";

	void networkMultiplayerPlayerJoinMenuUpdate();
	void networkMultiplayerPlayerJoinMenuRender();
	sp<OKMenu>networkMultiplayerPlayerJoinMenu = nullptr;
	sp<OKMenu>networkMultiplayerJoinedPeersMenu = nullptr;
	sp<OKMenu>networkMultiplayerRoomRulesMenu = nullptr;
	sp<Caption> networkMultiplayerPlayerJoinMenuPressStartCaption = nullptr;
	bool networkMultiplayerPlayerJoinMenuShowing = false;
	bool hosting = false;
	bool joining = false;
	
	bool hidePrivateRooms = false;
	bool hidePublicRooms = false;
	bool hideFreePlayRooms = false;
	bool hideTournamentRooms = false;
	string filterByGameSequenceName = "";
	string filterByGameSequenceUUID = "";
	string filterByGameTypeName = "";
	string filterByGameTypeUUID = "";
	string filterByKeyword = "";
	int filterByMaxPlayers = -1;

	long long lastSentPlayersUpdateTime = 0;
	long long lastSentServerRoomUpdateTime = 0;
	long long updatedJoinedPeersListTime = 0;
	//NETWORK

	long long lastTimeTriedToCloseGame = 0;
	virtual void tryToCloseGame() override;

	sp<CustomGameEditorControl>customGameEditor = nullptr;
	sp<GameSequenceEditorControl>gameSequenceEditor = nullptr;
	sp<GameTestMenuControl>gameTestMenu = nullptr;

	void customGameEditorMenuUpdate();
	void customGameEditorMenuRender();
	sp<OKMenu>customGameEditorMenu = nullptr;
	bool customGameEditorMenuShowing = false;
	int customGameEditorMenuCursorPosition = 0;
    

	void gameSequenceEditorMenuUpdate();
	void gameSequenceEditorMenuRender();
	sp<OKMenu>gameSequenceEditorMenu = nullptr;
	bool gameSequenceEditorMenuShowing = false;
	int gameSequenceEditorMenuCursorPosition = 0;

	void gameTestMenuUpdate();
	void gameTestMenuRender();
	//sp<OKMenu>gameTestMenu = nullptr;
	bool gameTestMenuShowing = false;
	int gameTestMenuCursorPosition = 0;


	void settingsMenuInit(sp<OKMenu> m, bool isSettingsMenu);
	void settingsMenuToggle(sp<OKMenu> m);
	void settingsMenuLeft(sp<OKMenu> m);
	void settingsMenuRight(sp<OKMenu> m);
	void settingsMenuSetDefaults(sp<OKMenu> m, bool isSettingsMenu);
	void globalSettingsMenuUpdate();
	void globalSettingsMenuRender();
	sp<OKMenu>globalSettingsMenu = nullptr;
	bool globalSettingsMenuShowing = false;
	int globalSettingsMenuCursorPosition = 0;

	void statsMenuUpdate();
	void statsMenuRender();
	sp<OKMenu>statsMenu = nullptr;
	sp<OKMenu>whichStatsMiniMenu = nullptr;
	bool whichStatsMiniMenuShowing = false;
	void resetAllStatsMenuVars();
	void whichStatsMiniMenuUpdate();
	bool statsMenuShowing = false;
	int statsMenuCursorPosition = 0;
	string statsMenu_difficultyName = "OVERALL";
	string statsMenu_gameSequenceOrTypeUUID = "OVERALL";
	string statsMenu_gameSequenceOrTypeName = "OVERALL";
	string statsMenu_objectiveName = "Play To Credits";
	bool updateStatsMenu = true;
	bool statsMenu_totalTimePlayed = false;
	bool statsMenu_totalBlocksCleared = false;
	bool statsMenu_planeswalkerPoints = false;
	bool statsMenu_eloScore = false;
	bool statsMenu_timeLasted = true;
	bool statsMenu_blocksCleared = false;


	void leftRightMenuAdjustFloat(float& variable, float min, float max, float minIncrement, float maxIncrement);
	void leftRightMenuAdjustInt(int& variable, int min, int max, int minIncrement, int maxIncrement);

	void saveRoomConfigMenuUpdate();
	sp<OKMenu>saveRoomConfigMenu = nullptr;
	bool saveRoomConfigMenuShowing = false;
	int saveRoomConfigMenuCursorPosition = 0;

	void loadRoomConfigMenuUpdate();
	sp<OKMenu>loadRoomConfigMenu = nullptr;
	bool loadRoomConfigMenuShowing = false;
	int loadRoomConfigMenuCursorPosition = 0;


	void roomOptionsMenuUpdate();
	//void roomOptionsMenuRender();
	sp<OKMenu>roomOptionsMenu = nullptr;
	bool roomOptionsMenuShowing = false;
	int roomOptionsMenuCursorPosition = 0;

	sp<Caption> descriptionCaption = nullptr;


	void gameSetupMenuUpdate();
	void gameSetupMenuRender();
	sp<OKMenu>gameSetupMenu = nullptr;
	bool gameSetupMenuShowing = false;
	int gameSetupMenuCursorPosition = 0;
	int selectedDifficultyIndex = 0;
	//int selectedObjectiveIndex = 0;

	//void selectedGameSequence(string name);
	//void selectedGameType(string name);
	//void selectedDifficulty(string name);
	//void selectedObjective(string name);

	void selectGameSequenceOrSingleGameTypeMenuUpdate();
	void selectGameSequenceOrSingleGameTypeMenuRender();
	sp<OKMenu>selectGameSequenceOrSingleGameTypeMenu = nullptr;
	bool selectGameSequenceOrSingleGameTypeMenuShowing = false;
	int selectGameSequenceOrSingleGameTypeMenuCursorPosition = 0;

	void selectGameSequenceMenuUpdate();
	void selectGameSequenceMenuRender();
	sp<OKMenu>selectGameSequenceMenu = nullptr;
	bool selectGameSequenceMenuShowing = false;
	int selectGameSequenceMenuCursorPosition = 0;

	double wilsonScore(double up, double total, double confidence = 1.644853);
	typedef sp<pair<string, sp<OKColor>>> StringColorPair;
	typedef sp<pair<sp<GameType>, StringColorPair>> GameTypeStringColorPairPair;
	typedef sp<pair<sp<GameSequence>, StringColorPair>> GameSequenceStringColorPairPair;

	//gameTypeOrSequenceString or difficulty string can be "OVERALL"
	sp<OKGameUserStatsForSpecificGameAndDifficulty> getUserStatsForGame(string gameTypeOrSequenceUUID, string difficultyString, string objectiveString);
	//gameTypeOrSequenceString or difficulty string can be "OVERALL"
	void populateUserStatsForSpecificGameAndDifficultyMenu(sp<OKMenu>menu, string gameTypeOrSequenceUUID, string difficultyString, string objectiveString);

	//gameTypeOrSequenceString or difficulty string can be "OVERALL"
	sp<OKGameLeaderBoardAndHighScoreBoard> getLeaderboardOrHighScoreBoardForGame(string gameTypeOrSequenceUUID, string difficultyString, string objectiveString,
		bool totalTimePlayed,
		bool totalBlocksCleared,
		bool planeswalkerPoints,
		bool eloScore,
		bool timeLasted,
		bool blocksCleared);

	//gameTypeOrSequenceString or difficulty string can be "OVERALL"
	string populateLeaderBoardOrHighScoreBoardMenu(sp<OKMenu>menu, string gameTypeOrSequenceUUID, string difficultyString, string objectiveString,
		bool totalTimePlayed,
		bool totalBlocksCleared,
		bool planeswalkerPoints,
		bool eloScore,
		bool timeLasted,
		bool blocksCleared
	);

	sp<vector<GameTypeStringColorPairPair>> getSortedGameTypes();
	sp<vector<GameSequenceStringColorPairPair>> getSortedGameSequences();
	void populateGameTypesMenu(sp<OKMenu>m);
	void populateGameSequencesMenu(sp<OKMenu>m);
	void selectSingleGameTypeMenuUpdate();
	//void selectSingleGameTypeMenuRender();
	sp<OKMenu>selectSingleGameTypeMenu = nullptr;
	bool selectSingleGameTypeMenuShowing = false;
	int selectSingleGameTypeMenuCursorPosition = 0;

	bool upRepeatedStarted = false;
	bool upRepeating = false;
	long long upLastTime = 0;

	bool downRepeatedStarted = false;
	bool downRepeating = false;
	long long downLastTime = 0;

	void gameSequenceOptionsMenuUpdate();
	void gameSequenceOptionsMenuRender();
	sp<OKMenu>gameSequenceOptionsMenu = nullptr;
	bool gameSequenceOptionsMenuShowing = false;
	int gameSequenceOptionsMenuCursorPosition = 0;

	void gameObjectiveMenuUpdate();
	//void gameObjectiveMenuRender();
	sp<OKMenu>gameObjectiveMenu = nullptr;
	bool gameObjectiveMenuShowing = false;
	int gameObjectiveMenuCursorPosition = 0;

	void sendGarbageToMenuUpdate();
	//void sendGarbageToMenuRender();
	sp<OKMenu>sendGarbageToMenu = nullptr;
	bool sendGarbageToMenuShowing = false;
	int sendGarbageToMenuCursorPosition = 0;

	void multiplayerOptionsMenuUpdate();
	void multiplayerOptionsMenuRender();
	sp<OKMenu>multiplayerOptionsMenu = nullptr;
	bool multiplayerOptionsMenuShowing = false;
	int multiplayerOptionsMenuCursorPosition = 0;

	//bool multiplayer_AllowDifferentDifficulties = true;
	//bool multiplayer_AllowDifferentGameSequences = true;
	//bool multiplayer_GameEndsWhenOnePlayerRemains = true;
	//bool multiplayer_GameEndsWhenSomeoneCompletesCreditsLevel = true;
	//bool multiplayer_DisableVSGarbage = false;

	bool localMultiplayer = false;
	bool networkMultiplayer = false;

	//sp<GameSequence>multiplayer_SelectedGameSequence = nullptr;
	//string multiplayer_SelectedDifficultyName = "Beginner";

	void sendGameStatsToServer();
	void doVoting();

	sp<OKMenu> statsUploadMenu = nullptr;
	bool sentStats = false;
	bool gotStatsResponse = false;
	long long firstCheckedStatsResponseTime = 0;
	long long lastCheckedStatsResponseTime = 0;

	sp<OKMenu> voteMenu = nullptr;
	bool sentVote = false;
	//bool voteUpDown = false;

	


	void playerGameSequenceMiniMenuUpdate(sp<PuzzlePlayer>p);
	void playerGameSequenceMiniMenuRender(sp<PuzzlePlayer>p, float x, float y);




	static sp<vector<sp<OKGameUserStatsForSpecificGameAndDifficulty>>>userStatsPerGameAndDifficulty;
	static sp<vector<sp<OKGameLeaderBoardAndHighScoreBoard>>>topPlayersByTotalTimePlayed;
	static sp<vector<sp<OKGameLeaderBoardAndHighScoreBoard>>>topPlayersByTotalBlocksCleared;
	static sp<vector<sp<OKGameLeaderBoardAndHighScoreBoard>>>topPlayersByPlaneswalkerPoints;
	static sp<vector<sp<OKGameLeaderBoardAndHighScoreBoard>>>topPlayersByEloScore;
	static sp<vector<sp<OKGameLeaderBoardAndHighScoreBoard>>>topGamesByTimeLasted;
	static sp<vector<sp<OKGameLeaderBoardAndHighScoreBoard>>>topGamesByBlocksCleared;



	void sendAllJoinedPeers(const string& s);
	void sendPeer(sp<UDPPeerConnection>c, const string& s);
	void sendAllPeers(const string& s);

	static const string lobbyCommand_STARTGAME;
	static const string lobbyCommand_CANCELGAME;
	static const string lobbyCommand_PEERGAMEJOIN;
	static const string lobbyCommand_PEERGAMELEAVE;
	static const string lobbyCommand_JOINEDPEER;
	static const string lobbyCommand_PLAYERCONFIRM;
	static const string lobbyCommand_PLAYERJOIN;
	static const string lobbyCommand_PLAYERLEAVE;
	static const string lobbyCommand_PLAYERFORFEIT;
	static const string lobbyCommandAllPeers_PLAYING;
	static const string lobbyCommandAllPeers_HOSTING;
	static const string lobbyCommandAllPeers_NOT_HOSTING;

	static const string netCommand_START;
	static const string netCommand_FRAME;
	static const string netCommand_FORFEIT;

	//sp<vector<sp<PuzzlePlayer>>>* bobsGameNetworkPlayers = ms<vector><sp<PuzzlePlayer>>();

	void tellAllPeersOneOfMyPlayersForfeitsGame(sp<PuzzlePlayer>p);
	//void cancelNetworkGame();
	void tellHostPeerIAmJoiningTheirGame();
	void tellAllPeersIAmHosting();
	void tellAllPeersIAmNotHosting();
	void tellAllJoinedPeersThatANewPeerHasJoinedMyHostedGame(sp<UDPPeerConnection>c);
	void tellAllPeersIAmPlayingAGame();
	void tellAllJoinedPeersIHaveCanceledMyHostedGame();
	void tellAllJoinedPeersMyHostedGameHasStarted();
	void tellAllJoinedPeersIHaveLeftTheGame();
	void tellAllJoinedPeersOneOfMyPlayersHasLeftTheLobby(sp<PuzzlePlayer>p);
	void tellAllJoinedPeersOneOfMyPlayersHasJoinedTheLobby(sp<PuzzlePlayer>p);
	void tellPeerThatOtherPeerHasJoined(sp<UDPPeerConnection> peerToTell, sp<UDPPeerConnection> joinedPeer);
	void tellPeerThatIHaveJoined(sp<UDPPeerConnection> peerToTell);
	void tellPeerThatPlayerHasJoined(sp<UDPPeerConnection> peerToTell, sp<PuzzlePlayer>p);
	void tellPeerThatPlayerHasConfirmedAndSendGameSequence(sp<UDPPeerConnection> peerToTell, sp<PuzzlePlayer>p);
	void tellAllPeersThatPlayerHasConfirmedAndSendGameSequence(sp<PuzzlePlayer>p);
	void tellServerIAmHostingOrUpdateRoomStatus(const string& roomDescription);
	void tellServerIHaveCanceledTheGame(const string& roomUUID);
	void tellServerIHaveStartedTheGame(const string& roomUUID);
	void tellServerTheGameHasEnded(const string& roomUUID, const string& results);
	static void getUserIDAndRandomSeedAndUUIDFromPlayerIDString(string s, long long &userID, long long &randomSeed, string& uuid);
	virtual bool udpPeerMessageReceived(sp<UDPPeerConnection>c, string s) override;

  
	static sp<vector<sp<GameType>>>loadedGameTypes;
	static sp<vector<sp<GameSequence>>>loadedGameSequences;
	static sp<vector<sp<Sprite>>>loadedSprites;
	void loadGameSequencesFromXML();
	void loadGameTypesFromXML();

	static void saveRoomConfigToFile(sp<Room> currentRoom, string name);
	static sp<vector<string>> getRoomConfigsList();
	static sp<Room> loadRoomConfig(string configName);

	static void saveUnknownGameSequencesAndTypesToXML(sp<GameSequence>gs);
	static void saveGameSequenceToXML(sp<GameSequence>gs, bool downloaded);
	static void saveGameTypeToXML(sp<GameType>gt, bool downloaded);
	static void loadGameSequenceUUIDsToGamesArray(sp<GameSequence>g);
	static sp<GameType> getGameTypeByName(string name);
	static sp<GameType> getGameTypeByUUID(string uuid);
	static sp<GameSequence> getGameSequenceByName(string name);
	static sp<GameSequence> getGameSequenceByUUID(string uuid);

	void increaseVolume();
	void decreaseVolume();

	void updateVersion0ToVersion1();



	bool wasAuthorizedWhenSent = false;
	bool gotGamesFromServer = false;
	bool sentHighScoresAndLeaderboardsRequestWhileLoggedIn = false;
	bool sentServerGamesRequest = false;
	long long lastCheckedGamesFromServerTime = 0;
	void getGameTypesAndSequencesFromServer();
	static void parseIncomingGameTypesAndSequencesFromServer_S(string &s);
	

	//------------------------------------

private:
	static queue<sp<GameType>> _incomingGameTypes;
	static mutex _incomingGameTypes_Mutex;
public:
	static int incomingGameTypesQueueSize_S()
	{
		lock_guard<mutex> lock(_incomingGameTypes_Mutex);
		return (int)_incomingGameTypes.size();
	}
	static sp<GameType> incomingGameTypesQueuePop_S()
	{
		lock_guard<mutex> lock(_incomingGameTypes_Mutex);
		sp<GameType>g = _incomingGameTypes.front();
		_incomingGameTypes.pop();
		return g;
	}
	static void incomingGameTypesQueuePush_S(sp<GameType>p)
	{
		lock_guard<mutex> lock(_incomingGameTypes_Mutex);
		_incomingGameTypes.push(p);
	}
	//------------------------------------

	//------------------------------------

private:
	static queue<sp<GameSequence>> _incomingGameSequences;
	static mutex _incomingGameSequences_Mutex;
public:
	static int incomingGameSequencesQueueSize_S()
	{
		lock_guard<mutex> lock(_incomingGameSequences_Mutex);
		return (int)_incomingGameSequences.size();
	}
	static sp<GameSequence> incomingGameSequencesQueuePop_S()
	{
		lock_guard<mutex> lock(_incomingGameSequences_Mutex);
		sp<GameSequence>g = _incomingGameSequences.front();
		_incomingGameSequences.pop();
		return g;
	}
	static void incomingGameSequencesQueuePush_S(sp<GameSequence>p)
	{
		lock_guard<mutex> lock(_incomingGameSequences_Mutex);
		_incomingGameSequences.push(p);
	}
	//------------------------------------

	//------------------------------------
	private:
		static bool _gotIncomingGamesFromServer;
		static mutex _gotIncomingGamesFromServer_Mutex;
public:
	static void setGotIncomingGamesFromServer_S(bool b)
	{
		lock_guard<mutex> lock(_gotIncomingGamesFromServer_Mutex);
		_gotIncomingGamesFromServer = b;
	}
	static bool getAndResetGotIncomingGamesFromServer_S()
	{
		lock_guard<mutex> lock(_gotIncomingGamesFromServer_Mutex);
		if(_gotIncomingGamesFromServer)
		{
			_gotIncomingGamesFromServer = false;
			return true;
		}
		else
		{
			return false;
		}
	}
	//------------------------------------

	long long lastCheckedGotIncomingGamesFromServerTime = 0;
};


