
class ExpansionUH extends House
{
	ref Helicrash_Settings m_ActiveHelicrash_Settings;
	ref CrashLocations m_ActiveCrashLocations;

	protected EffectSound m_Sound;

	protected bool m_HasCrashed;
	protected float m_RotationalA;
	protected float m_Radius;
	protected vector m_Location;
	
	protected float m_height = 250;
	protected float m_speed = 50;
	protected float m_minimum_speed = 25;
	
	Particle m_ParticleEfx;
	
	protected float m_RotorSpeed;
	protected float m_RotorAnimationPosition;
			
	void Helicopter_Fly(ref CrashLocations activeCrashLocations)
	{
		m_ActiveCrashLocations = activeCrashLocations;

		m_Location = Vector(m_ActiveCrashLocations.x, 0, m_ActiveCrashLocations.y);
		m_Radius = m_ActiveCrashLocations.Radius;

		vector position = GetPosition();
		m_RotationalA = Math.Atan2( m_ActiveCrashLocations.y - position[2], m_ActiveCrashLocations.x - position[0] );
	}

	void ExpansionUH()
	{	
		m_ActiveHelicrash_Settings = Helicrash_Settings.Load();

		SetEventMask( EntityEvent.CONTACT | EntityEvent.SIMULATE );

		if (GetGame().IsClient() || !GetGame().IsMultiplayer())
			PlayHelicopterAudio();
	}
	
	void ~ExpansionUH()
	{
		if (m_Sound)
			m_Sound.Stop();
	}

	void PlayHelicopterAudio()
	{
		if (GetGame().GetPlayer()) 
		{
			PlaySoundLoop("Expansion_Mi8_Base_Loop_Int", 1000);
		}
	}

	override void EOnSimulate( IEntity owner, float dt )
	{
		if ( GetGame().IsServer() )
		{	
			//removes the blur around the main rotor
			//HideSelection( "hiderotorblur" );
			this.ShowSelection( "hiderotorblur" );
			this.HideSelection( "hiderotor" );
			
			m_RotorAnimationPosition += 0.95 * dt * 0.5;
			
			if ( m_RotorAnimationPosition >= 1 )
				m_RotorAnimationPosition -= 1;
		
			SetAnimationPhase( "rotor", m_RotorAnimationPosition );
			SetAnimationPhase( "rearrotor", m_RotorAnimationPosition );
		
			vector position = GetPosition();

			vector velocity = Vector( Math.Cos( m_RotationalA ), 0, Math.Sin( m_RotationalA ) );

			for (int d = 0; d < m_ActiveHelicrash_Settings.HelicopterUS_.Count(); d++)
			{
				m_speed = m_ActiveHelicrash_Settings.HelicopterUS_.Get(d).speed;
				m_minimum_speed = m_ActiveHelicrash_Settings.HelicopterUS_.Get(d).minimum_speed;
			}
			
			//m_speed = 1000;
			
			velocity[0] = velocity[0]  * (m_speed) * dt;
			velocity[2] = velocity[2]  * (m_speed) * dt;
			
			vector transform[4];
			GetTransform( transform );
			transform[3] = transform[3] + velocity;
			transform[3][1] = GetGame().SurfaceY(GetPosition()[0], GetPosition()[2]) + m_height; //height

			MoveInTime( transform, dt );
			
			float distance_ = Math.Sqrt(Math.Pow(m_Location[0] - GetPosition()[0], 2) + Math.Pow(m_Location[2] - GetPosition()[2], 2));
			
			if (distance_ >= 2000 && m_height >= 50)
			{
				m_height--; //decrease the height until 50m
			}
	
			if (distance_ <= 2000)
			{
			  	m_speed = m_minimum_speed;
			}

			Helicopter_Crash_Stage_Explosion();
		}
	}

	override void EEDelete(EntityAI parent)
	{
		if ( !GetGame().IsMultiplayer() || GetGame().IsClient() )
		{
			if ( m_ParticleEfx )
				m_ParticleEfx.Stop();
		}
	}

	void Helicopter_Crash_Stage_Explosion()
	{
		float dist = Math.Sqrt(Math.Pow(m_Location[0] - GetPosition()[0], 2) + Math.Pow(m_Location[2] - GetPosition()[2], 2));
		
		if (dist <= Math.RandomFloat(0, m_Radius)) 
		{
			if (!m_HasCrashed) //has created heli crash!?
			{
				CreateHeliCrash();
				m_HasCrashed = true;
			}
		}
	}

	void CreateHeliCrash()
	{
		Object drop = Object.Cast( GetGame().CreateObject( "ExpansionUH_Crash", Vector( GetPosition()[0], GetPosition()[1], GetPosition()[2]) ));	
						
		drop.SetPosition(Vector( GetPosition()[0], GetPosition()[1], GetPosition()[2]));	//sets the position to the exact position within radius of the helicopter
		drop.SetOrientation(Vector(GetOrientation()[0], GetOrientation()[1], GetOrientation()[2])); //set the helicopter the same direction as the primary helicopter

		GetGame().GetCallQueue( CALL_CATEGORY_SYSTEM ).CallLater( GetGame().ObjectDelete, 0, false, this );
	}
}