#include <Player.h>

Player::Player()
{
	DEBUG_MSG("Constructing Player");
}

Player::~Player()
{
	DEBUG_MSG("Destructing Player");
}

void Player::Initialize(const GameObjectParameters* params)
{
	DEBUG_MSG("Player Initializing");
	this->SetX(params->GetX());
	this->SetY(params->GetY());
}

void Player::Render()
{
	DEBUG_MSG("Player Drawing");
}

void Player::Update()
{
	DEBUG_MSG("Player Updating");
}

void Player::CleanUp()
{
	DEBUG_MSG("Cleaning Up Player");
}
