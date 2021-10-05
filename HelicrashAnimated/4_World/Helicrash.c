/*

TODO,
Clean me the fuck up 
Add crash prevention to incorrect json ChatLine

*/

class HelicopterRU
{
	int start_height;
	int minimum_height;
	int speed;
	int minimum_speed;
	
 	void HelicopterRU(int start_height_, int minimm_height_, int speed_, int minimum_speed_) 
	{
        start_height = start_height_;
        minimum_height = minimm_height_;
        speed = speed_;
        minimum_speed = minimum_speed_;
    }
}

class HelicopterUS
{
	int start_height;
	int minimum_height;
	int speed;
	int minimum_speed;
	
 	void HelicopterUS(int start_height_, int minimm_height_, int speed_, int minimum_speed_) 
	{
        start_height = start_height_;
        minimum_height = minimm_height_;
        speed = speed_;
        minimum_speed = minimum_speed_;
    }
}

class CrashLocations
{
    float x, y;
    float Radius;
    string Crash_Message;

    void CrashLocations(float x_, float y_, float Radius_, string Crash_Message_) 
	{
        x = x_;
        y = y_;
        Radius = Radius_;
        Crash_Message = Crash_Message_;
    }
}

class AnimalsSpawn
{
	ref TStringArray animal_name;
	int radius;
	
	int amount_minimum;
	int amount_maximum;

	void AnimalsSpawn(TStringArray animal_name_, int radius_, int amount_minimum_, int amount_maximum_)
	{
		animal_name = animal_name_;
		radius = radius_;
		amount_minimum = amount_minimum_;
		amount_maximum = amount_maximum_;
		
	}
}

class ZombieSpawn
{
	ref TStringArray zombie_name;
	int radius;
	int amount_minimum;
	int amount_maximum;
	
	void ZombieSpawn(ref TStringArray zombie_name_, int radius_, int amount_minimum_, int amount_maximum_)
	{
		zombie_name = zombie_name_;
		radius = radius_;
		amount_minimum = amount_minimum_;
		amount_maximum = amount_maximum_;
	}
}

class CrashLootRUWeapons
{
	string WeaponName;
	ref TStringArray Magazines;
	ref TStringArray Attachments;
	string Sight;
	
	void CrashLootRUWeapons( string WeaponName_, ref TStringArray Magazine_, ref TStringArray Attachments_, string Sight_)
	{
		WeaponName = WeaponName_;
		Magazines = Magazine_;
		Attachments = Attachments_;
		Sight = Sight_;
	}
}

class CrashLootUSWeapons
{
	string WeaponName;
	ref TStringArray Magazines;
	ref TStringArray Attachments;
	string Sight;
	
	void CrashLootUSWeapons( string WeaponName_, ref TStringArray Magazine_, ref TStringArray Attachments_, string Sight_)
	{
		WeaponName = WeaponName_;
		Magazines = Magazine_;
		Attachments = Attachments_;
		Sight = Sight_;
	}
}

class Helicrash_Settings
{
	int Maximum_Loot_RU;
	int Maximum_Loot_US;
	
	int Helicrash_Time; 
	
	ref array< ref CrashLocations > CrashPoints;
	
	ref array< ref HelicopterUS > HelicopterUS_;
	ref array< ref HelicopterRU > HelicopterRU_;
	
	ref array< ref AnimalsSpawn > AnimalSpawnArray;
	ref array< ref ZombieSpawn > ZombieSpawnArray;
	
	ref TStringArray Loot_US;
	ref TStringArray Loot_RU;
	
	ref array< ref CrashLootUSWeapons > WeaponLootTables_US;
	ref array< ref CrashLootRUWeapons > WeaponLootTables_RU;

	void Helicrash_Settings()
	{
		CrashPoints = new ref array< ref CrashLocations >;
		
		HelicopterUS_ = new ref array< ref HelicopterUS >;
		HelicopterRU_ = new ref array< ref HelicopterRU >;
		
		AnimalSpawnArray = new ref array< ref AnimalsSpawn >;
		ZombieSpawnArray = new ref array<ref ZombieSpawn>;
		
		Loot_US = new ref TStringArray;
		Loot_RU = new ref TStringArray;
		
		WeaponLootTables_US = new ref array< ref CrashLootUSWeapons >;
		WeaponLootTables_RU = new ref array<ref CrashLootRUWeapons>;
	}
		
	void SetupJSONCFG()
	{
		Helicrash_Time = 30;
		
        Maximum_Loot_RU = 1;
	    Maximum_Loot_US = 1;
		
		CrashPoints.Insert( new ref CrashLocations(4893, 9660, 100, "Helicopter crashing near xyz") );
		CrashPoints.Insert( new ref CrashLocations(5216.25, 8850, 100, "Helicopter crashing near xyz") );
		CrashPoints.Insert( new ref CrashLocations(5418.75, 8385, 100, "Helicopter crashing near xyz") );

		HelicopterRU_.Insert(new ref HelicopterRU(250, 50, 50, 25));
		HelicopterUS_.Insert(new ref HelicopterUS(250, 50, 50, 25));
		
		AnimalSpawnArray.Insert( new ref AnimalsSpawn({"Animal_BosTaurusF_Brown"}, 10, 1, 5) );
		ZombieSpawnArray.Insert( new ref ZombieSpawn({"ZmbM_usSoldier_normal_Woodland"}, 10, 1, 5) );
		
		Loot_US.Insert("MRE");
		Loot_US.Insert("MRE");
		
		Loot_RU.Insert("MRE");
		Loot_RU.Insert("MRE");

		WeaponLootTables_US.Insert( new ref CrashLootUSWeapons("M4A1", {"Mag_STANAG_30Rnd"}, {"M4_Suppressor"}, "M68Optic"));
		WeaponLootTables_RU.Insert( new ref CrashLootRUWeapons("M4A1", {"Mag_STANAG_30Rnd"}, {"M4_Suppressor"}, "M68Optic"));

		JsonFileLoader<Helicrash_Settings>.JsonSaveFile( PATH_HELICRASH, this );
	}

	static ref Helicrash_Settings Load()
	{
		ref Helicrash_Settings Helicopter_Settings = new Helicrash_Settings();
		
		if ( FileExist( PATH_HELICRASH ) )
		{
			JsonFileLoader<Helicrash_Settings>.JsonLoadFile( PATH_HELICRASH, Helicopter_Settings );
		} 
		else 
		{
			Helicopter_Settings.SetupJSONCFG();
		}
			
		return Helicopter_Settings;
	}
}

class HelicrashBase
{	
	protected ref array< ExpansionUH > m_Helicopter_UH1H;
	
	ref Helicrash_Settings m_ActiveHelicrash_Settings;
	ref CrashLocations m_ActiveCrashLocations;
	
	protected ref Timer m_HelicopterTimer;
						
	void HelicrashBase()
	{
		m_Helicopter_UH1H = new array<ExpansionUH>;
		
		m_ActiveHelicrash_Settings = Helicrash_Settings.Load();
		m_ActiveCrashLocations = m_ActiveHelicrash_Settings.CrashPoints.GetRandomElement();

		m_HelicopterTimer = new Timer();
				
		int Helicopter_CrashTime = m_ActiveHelicrash_Settings.Helicrash_Time;
		
		if (Helicopter_CrashTime <= 0)
		{
			Helicopter_CrashTime = 30;
			Print("Helicrash_Time == 0 adjusting to 30 minutes");
		}
	
		if (m_ActiveCrashLocations == null)
			Print("Nullptr");
		
		Print("Helicopters will crash every" + " " + Helicopter_CrashTime + " Minutes");
		
		m_HelicopterTimer.Run(Helicopter_CrashTime * 60, this, "SpawnCrash", new Param2<bool, vector>(false, vector.Zero), true);		
	}
	
	void ClientCallCrash(PlayerBase player, vector PlayerPosition) // client has called a helicopter crash to their location
	{
		Print("Client Called Crash");
		
		if (player) 
		{
			PlayerIdentity identity = player.GetIdentity();
			
			if (identity) 
			{
				SpawnCrash(true, PlayerPosition);
			}
		} 
	}
	
	void SpawnCrash(bool did_user_call, vector loc)
	{		
		if (did_user_call)
		{
			Print("Spawn Crash - Client");
			m_ActiveCrashLocations.x = loc[0];
			m_ActiveCrashLocations.y = loc[2];
		}
		else
		{
			Print("Spawn Crash - Server");
			m_ActiveCrashLocations = m_ActiveHelicrash_Settings.CrashPoints.GetRandomElement();
		}
						
		int randomized_helicopter_spawn = Math.RandomInt(0, 3); //randomizes the start location OUT OF THE MAP so they fly in you can add more
		
		vector helicopter_spawn;
		
		if (randomized_helicopter_spawn == 0)
		{
			helicopter_spawn[0] = 5752.5;
			helicopter_spawn[2] = 997.5;
		}
		else if (randomized_helicopter_spawn == 1)
		{
			helicopter_spawn[0] = 14775;
			helicopter_spawn[2] = 8175;
		}
		else if (randomized_helicopter_spawn == 2)
		{
			helicopter_spawn[0] = 7965;
			helicopter_spawn[2] = 15300;
		}
		
		int random = 1;
		
		/*
		
			Random == The helicopter model
			0 = Russian
			1 = USA
		*/
		
		switch(random) //spawns the helicopters
		{
			case 0:
			{
				
			}
			case 1:
			{
				ExpansionUH helicopter_uh1h = ExpansionUH.Cast( GetGame().CreateObject( "ExpansionUH", helicopter_spawn, false, true, true) );
		
				helicopter_uh1h.SetPosition(helicopter_spawn); 
				
				if (helicopter_uh1h)
				{
					m_Helicopter_UH1H.Insert( helicopter_uh1h );
				}

				vector Helicopter_SpawnUS;
				
				Helicopter_SpawnUS[0] = m_ActiveCrashLocations.x;
				Helicopter_SpawnUS[2] = m_ActiveCrashLocations.y;

				helicopter_uh1h.Helicopter_Fly(m_ActiveCrashLocations);
				helicopter_uh1h.SetDirection(helicopter_spawn - Helicopter_SpawnUS); //we need the direction to be set the same otherwise the helicopter flys in a stupid position
				break;
			}
		}
	}
}

static ref HelicrashBase g_HelicrashBase;
static ref HelicrashBase GetHelicrashBase()
{
    if ( !g_HelicrashBase )
    {
         g_HelicrashBase = new ref HelicrashBase();
    }
    
    return g_HelicrashBase;
}