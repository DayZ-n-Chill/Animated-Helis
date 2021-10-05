class ExpansionUH_Crash extends House
{
	protected Particle m_ParticleEfx;
	protected Particle m_SmokeEfx;
	protected Particle m_ExpansionEfx;
	
	ref Timer m_Timer;
	ref Timer m_RemovalTimer;
	ref Helicrash_Settings m_ActiveHelicrash_Settings;

	protected bool m_Loot;
	protected bool m_IsDeleted;
	protected bool m_bShouldDeleteSmoke;
	
	protected vector m_GroundPos;
		
	void ExpansionUH_Crash()
	{
		m_ActiveHelicrash_Settings = Helicrash_Settings.Load();

		ExpansionMi8_Crash_Init();
					
		if (GetGame().IsClient() || !GetGame().IsMultiplayer())
			PlayAudioClient();
	}	
	
	
	void PlayAudioClient()
	{
		if (GetGame()) 
		{
			if (GetGame().GetPlayer()) 
			{
				PlaySound("Explosion_Init", 1000);
			}
		}
	}
	
	void ~ExpansionUH_Crash()
	{
		if (m_ParticleEfx)
			m_ParticleEfx.Stop();
		
		if(m_ExpansionEfx)
			m_ExpansionEfx.Stop();
		
		if (m_Timer) 
			m_Timer.Stop();
		
		if (m_RemovalTimer) 
			m_RemovalTimer.Stop();
	}

	void ExpansionMi8_Crash_Init()
	{
		vector m_TempPos = GetPosition();
		vector m_TempOri = GetOrientation();

		if (GetGame().IsClient() || !GetGame().IsMultiplayer()) 
		{
			m_ParticleEfx = Particle.PlayOnObject(ParticleList.SMOKING_HELI_WRECK,this, Vector(-0.5, 0, -1.0));
			m_ExpansionEfx = Particle.PlayOnObject( ParticleList.EXPANSION_FIRE_HELICOPTER, this, Vector(-0.10, 0, -1.0)); //remove this if no usage of Expansion
		}

		if (GetGame().IsServer()) 
		{
			SetOrientation(Vector(GetOrientation()[0], 0, 0));
			SetDirection(GetDirection());

			m_Timer = new Timer();
			m_Timer.Run(0.07, this, "Helicrash_Stage_Crash", NULL, true);
		}
		
		if ( !GetGame().IsMultiplayer() || GetGame().IsClient() )
		{
			m_RemovalTimer = new Timer();
			m_RemovalTimer.Run(0.07, this, "Despawn_HeliCrashMI", NULL, true);
		}			
	}
	
	void Despawn_HeliCrashMI()
	{
		if (m_IsDeleted && m_bShouldDeleteSmoke)
		{
			if ( !GetGame().IsMultiplayer() || GetGame().IsClient() )
			{
				if (m_ParticleEfx)
					m_ParticleEfx.Stop();
			
				if (m_ExpansionEfx)
					m_ExpansionEfx.Stop();
			}
		}	
	}
	
	void Helicrash_Rotate()
	{
		if (GetVelocity(this).Length() >= 0) 
		{
			CreateDynamicPhysics(PhxInteractionLayers.DYNAMICITEM);
			EnableDynamicCCD(true);

			SetOrientation(Vector(GetOrientation()[0] + 5, 0, 0)); //spin the object
			SetVelocity(this, Vector(25, -10, 0));
		}
	}
	static Weapon_Base CreateWeaponWithMagazine( string sWeapon, string sMagazine, vector pos )
	{
	    Weapon_Base oWpn = Weapon_Base.Cast(GetGame().CreateObject( sWeapon , pos ));
	
	    if ( !oWpn )
	        return NULL;
	
		int stateId = -1;
	
		if ( oWpn.IsInherited( SKS_Base ) )
			return oWpn;
		else if ( oWpn.IsInherited( BoltActionRifle_InnerMagazine_Base ) )
			return oWpn;
		else if ( oWpn.IsInherited( DoubleBarrel_Base ) )
			return oWpn;
		else if ( oWpn.IsInherited( Pistol_Base ) )
			stateId = PistolStableStateID.CLO_DIS_BU0_MA1;
		else if ( oWpn.IsInherited( CZ527_Base ) )
			stateId = CZ527StableStateID.CZ527_CLO_BU0_MA1;
		else if ( oWpn.IsInherited( Repeater_Base ) )
			return oWpn;
		else if ( oWpn.IsInherited( RifleBoltFree_Base ) )
			stateId = RBFStableStateID.RBF_CLO_BU0_MA1;
		else if ( oWpn.IsInherited( RifleBoltLock_Base ) )
			stateId = RBLStableStateID.RBL_OPN_BU0_MA1;
		else if ( oWpn.IsInherited( Mp133Shotgun_Base ) )
			return oWpn;
	
		
		InventoryLocation mag_il = new InventoryLocation;
		
		mag_il.SetAttachment( oWpn, NULL, InventorySlots.MAGAZINE );
		
		Magazine oMag = Magazine.Cast( SpawnEntity( sMagazine, mag_il, ECE_IN_INVENTORY, RF_DEFAULT ) );
	    
		if ( !oMag )
	        return oWpn;
	    
		GetGame().RemoteObjectDelete( oWpn );
		GetGame().RemoteObjectDelete( oMag );
	    
	
		pushToChamberFromAttachedMagazine( oWpn, oWpn.GetCurrentMuzzle() );
	
		ScriptReadWriteContext ctx = new ScriptReadWriteContext;
		ctx.GetWriteContext().Write( stateId );
		oWpn.LoadCurrentFSMState( ctx.GetReadContext(), GetGame().SaveVersion() );
	

		GetGame().RemoteObjectCreate( oWpn );
		GetGame().RemoteObjectCreate( oMag );
		  
	    return oWpn;
	}
	void Helicrash_SpawnLoot()
	{
		if (m_IsDeleted)
			return;
		
		vector orientation;
		
		SetVelocity( this, Vector( 0, 0, 0 ) );

        dBodySetAngularVelocity( this, Vector( 0, 0, 0 ) );
        dBodyActive( this, ActiveState.INACTIVE );
        dBodyDynamic( this, false );
        dBodyDynamic( this, false );
		
		SetDirection(GetDirection());
		SetOrientation(Vector(GetOrientation()[0], 0, 0));
		
		orientation = GetOrientation();
		
		PlaceOnSurface();
		
		SetPosition(m_GroundPos);
		
		if (!m_Loot)
		{
			for (int ac = 0; ac < m_ActiveHelicrash_Settings.AnimalSpawnArray.Count(); ac++) 
			{
				ref AnimalsSpawn AnimalSpawnArray = m_ActiveHelicrash_Settings.AnimalSpawnArray.Get(ac);

				int animal_spawn = Math.RandomInt(AnimalSpawnArray.amount_minimum, AnimalSpawnArray.amount_maximum);
				
				for (int SpawnCountA = 0; SpawnCountA < animal_spawn; SpawnCountA++) 
				{
					vector Animal_Spawn = m_GroundPos;
					
					Animal_Spawn[0] = Animal_Spawn[0] + (2.5 * Math.Cos(SpawnCountA));
					Animal_Spawn[2] = Animal_Spawn[2] + (2.5 * Math.Sin(SpawnCountA));
					Animal_Spawn[1] = GetGame().SurfaceY(Animal_Spawn[0], Animal_Spawn[2]) + 0.2;
					
					GetGame().CreateObject(AnimalSpawnArray.animal_name.GetRandomElement(), Animal_Spawn, false, true);
				}
				
			}
				
			for (int zb = 0; zb < m_ActiveHelicrash_Settings.ZombieSpawnArray.Count(); zb++) 
			{
				ref ZombieSpawn ZombieSpawnArray = m_ActiveHelicrash_Settings.ZombieSpawnArray.Get(zb);

				int ZombieSpawnAmount = Math.RandomInt(ZombieSpawnArray.amount_minimum, ZombieSpawnArray.amount_maximum);
				
				for (int SpawnCountZ = 0; SpawnCountZ < ZombieSpawnAmount; SpawnCountZ++) 
				{
					vector Zombie_Spawn = m_GroundPos;
					
					Zombie_Spawn[0] = Zombie_Spawn[0] + (2.5 * Math.Cos(SpawnCountZ));
					Zombie_Spawn[2] = Zombie_Spawn[2] + (2.5 * Math.Sin(SpawnCountZ));
					Zombie_Spawn[1] = GetGame().SurfaceY(Zombie_Spawn[0], Zombie_Spawn[2]) + 0.2;
					
					GetGame().CreateObject(ZombieSpawnArray.zombie_name.GetRandomElement(), Zombie_Spawn, false, true);
				}
				
			}
			
			if (!m_Loot)
			{
				ref TStringArray Loot_Tables_ = new TStringArray;

				for (int ab = 0; ab < m_ActiveHelicrash_Settings.Loot_US.Count(); ab++) 
				{
					Loot_Tables_.Insert(m_ActiveHelicrash_Settings.Loot_US.Get(ab));
				}
				
				for (int i = 0; i < m_ActiveHelicrash_Settings.Maximum_Loot_US; i++) 
				{
					//Print(i);
							
					vector loot_pos = m_GroundPos;
							
					loot_pos[0] = loot_pos[0] + (2.5 * Math.Cos(i));
					loot_pos[2] = loot_pos[2] + (2.5 * Math.Sin(i));
					loot_pos[1] = GetGame().SurfaceY(loot_pos[0], loot_pos[2]) + 0.2;
		
					Print(Loot_Tables_.GetRandomElement());
					EntityAI weaponEnt;
					weaponEnt = EntityAI.Cast( GetGame().CreateObject(Loot_Tables_.GetRandomElement(), loot_pos, false, true) );
							
					if (i == m_ActiveHelicrash_Settings.Maximum_Loot_US - 1) //our loop == the maximum we set in our loot tables
					{
						m_Loot = true; //set this to true so we don't run this a second time?
					}
				}
				
				for (int v = 0; v < 1; v++)
				{
					for (int j = 14; j < m_ActiveHelicrash_Settings.WeaponLootTables_US.Count(); j++)
					{
						CrashLootUSWeapons WeaponLootTables_US;
					
						WeaponLootTables_US = m_ActiveHelicrash_Settings.WeaponLootTables_US.GetRandomElement();
					
						if (WeaponLootTables_US)
						{
							vector loot_pos_ = m_GroundPos;
								
							loot_pos_[0] = loot_pos_[0] + (3.5 * Math.Cos(i));
							loot_pos_[2] = loot_pos_[2] + (3.5 * Math.Sin(i));
							loot_pos_[1] = GetGame().SurfaceY(loot_pos_[0], loot_pos_[2]) + 0.2;
			
							string weapon_name = WeaponLootTables_US.WeaponName;
							string Sight = WeaponLootTables_US.Sight;
	
							Weapon_Base weapon;
							ItemBase optic;
												
							if (WeaponLootTables_US.Magazines.Count() > 0)
							{
								weapon = CreateWeaponWithMagazine( WeaponLootTables_US.WeaponName, WeaponLootTables_US.Magazines.Get(0), loot_pos_);
		
							}
							else
							{
								weapon = Weapon_Base.Cast( GetGame().CreateObject(WeaponLootTables_US.WeaponName, loot_pos_, false, true) );
							}
						
							if (WeaponLootTables_US.Attachments.Count() > 0 )
							{
								for (int attch = 0; attch < WeaponLootTables_US.Attachments.Count(); attch++)
								{
									weapon.GetInventory().CreateAttachment( WeaponLootTables_US.Attachments.Get(attch) );
								}	
							}
						
							if (WeaponLootTables_US.Sight != "")
							{
								optic = weapon.GetInventory().CreateAttachment( WeaponLootTables_US.Sight );
								optic.GetInventory().CreateAttachment("Battery9V");
							}
						}
					}
				}
				m_Loot = true;
			}
		}
			
		if (this && !m_IsDeleted)
		{
			GetGame().ObjectDelete(this);
				
			m_IsDeleted = true;
			m_bShouldDeleteSmoke = true;
		}
			
		Object helicopter_US_CRASH = GetGame().CreateObject( "Wreck_UH1Y", m_GroundPos, false, true, true);
		helicopter_US_CRASH.SetOrientation(Vector(orientation[0], 0, 0));
		Print("Helicopter " + GetModelName() + " " + "Crashed at " + m_GroundPos);

	}

	void Helicrash_Stage_Crash()
	{
		if (GetGame().IsServer() && !m_IsDeleted) 
		{
			if (!IsHitTheGround(1.9)) 
			{
				Helicrash_Rotate();
			}
			else 
			{
				
				m_GroundPos = GetPosition();
				Helicrash_SpawnLoot();		
			}
		}
	}

	bool IsHitTheGround(float height)
	{
		vector m_Start = this.GetPosition();
		vector m_End = this.GetPosition() - Vector(0, height, 0);
		
		vector m_Hit;
		vector m_HitPos;
		
		int m_HitIndex;

		return DayZPhysics.RaycastRV(m_Start, m_End, m_HitPos, m_Hit, m_HitIndex, NULL, NULL, this);
	}

	bool IsObject()
	{
		set<Object> objects = new set<Object>;

		objects.Clear();

		vector m_Start = this.GetPosition();
		vector m_End = this.GetPosition() - Vector(0, 5, 0);
		
		vector m_Hit;
		vector m_HitPos;
		
		int m_HitIndex;

		DayZPhysics.RaycastRV(m_Start, m_End, m_HitPos, m_Hit, m_HitIndex, objects, NULL, this);

		return objects.Count() != 0;
	}

	override bool CanPutIntoHands( EntityAI parent )
	{
		return false;
	}

	override bool CanPutInCargo ( EntityAI parent )
	{
		return false;
	}

	override bool IsInventoryVisible()
    {
        return true;
    }

	override bool CanUseConstruction()
    {
        return true;
    }
}