#include "RigidBody.h"
#include "..\Common.h"

using namespace nsEngine;
using namespace nsEngine::nsPhysics;
using namespace nsEngine::nsMaths;

RigidBody::RigidBody()
	: m_Vec3Scale(1, 1 ,1)
	, m_RotDegree(0)
	, m_Gravity(nsCommon::gGRAVITY)
	, m_Friction(nsCommon::gFRICTION)
{}

void RigidBody::Initialize(const Vector3 &pos, const Vector3 &scale, const double rotation,
							const Vector3 &velocity, const double gravity, const double friction)
{
	m_Vec3Pos = pos;
	m_Vec3Scale = scale;
	m_RotDegree = rotation;
	m_Vec3Velocity = velocity;
	m_Gravity = gravity;
	m_Friction = friction;
}

void RigidBody::Update()
{}

void RigidBody::Render()
{}