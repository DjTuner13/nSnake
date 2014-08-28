#ifndef STATEMANAGER_H_DEFINED
#define STATEMANAGER_H_DEFINED

#include <Engine/Flow/GameState.hpp>
#include <exception>

/// Custom exception that's used to instantly
/// change from one state to another.
///
class StateManagerChangeException : public std::exception
{
public:
	StateManagerChangeException(GameState* newState):
		newState(newState)
	{ }

	GameState* newState;
};

/// Custom exception for the specific case of
/// quitting the game.
///
/// Quile like the custom exception above.
///
class StateManagerQuitException : public std::exception
{
public:
	StateManagerQuitException()
	{ }
};

/// Giga-class that switches from game states.
///
/// It makes the transitions between them, assuring each one is
/// properly initialized.
///
/// ## For developers:
///
/// Short and simple explanation:
///
/// * Creates the first state (allocating everything).
/// * Run it (updating and drawing).
/// * Whenever the state feels like changing, it will tell us
///   (quit, for example).
/// * Then we must delete the current state and repeat this whole
///   process for the next one.
///
class StateManager
{
public:
	/// Immediately changes to #newState
	///
	/// @note Don't worry, it cleans up the current
	///       GameState before.
	///
	static void change(GameState* newState);

	/// Immediately quits the game.
	///
	/// @note Don't worry, it cleans up the current
	///       GameState before.
	///
	static void quit();

	/// Initializes pretty much everything,
	/// setting #initialState to run first.
	///
	/// @note It only actually starts when you call #run()
	StateManager(GameState* initialState);

	virtual ~StateManager();

	/// Main entry point and game loop.
	///
	/// This is where it all happens. The game never leaves this
	/// method, the only thing that's allowed to happen are
	/// state-specific methods called inside here.
	///
	/// If we leave this method, the game quits, as seen on
	/// *main.cpp*.
	void run();

private:

	/// Current game state - defines what will actually happen.
	GameState* currentState;

	/// Shared information between states.
	///
	/// If a state want to share something with another, it should
	/// return a value that will be stored right here.
	///
	/// Perhaps I should make this a template class or something.
	int sharedInfo;
};

#endif /* STATEMANAGER_H_DEFINED */

