modded class Wreck_UH1Y extends House
{
	Particle m_ParticleEfx;
	protected vector m_crashpos;
	protected bool m_ShouldDeleteSmoke;
	
	ref Timer m_RemovalTimer_UH1H;
	
	void Wreck_UH1Y()
	{
		if ( !GetGame().IsMultiplayer() || GetGame().IsClient() )
		{
			m_ParticleEfx = Particle.PlayOnObject(ParticleList.SMOKING_HELI_WRECK, this, Vector(-0.5, 0, -1.0));
		}
		
		if (GetGame().IsServer()) 
		{
			GetGame().GetCallQueue( CALL_CATEGORY_GAMEPLAY ).CallLater(Destroy_Wreck, 3600000, false);
		}
		
		if ( !GetGame().IsMultiplayer() || GetGame().IsClient() )
		{
			m_RemovalTimer_UH1H = new Timer();
			m_RemovalTimer_UH1H.Run(0.07, this, "RemovalFunction", NULL, true);
		}		
	}
	
	void RemovalFunction()
	{
		if (m_ShouldDeleteSmoke)
		{
			if ( !GetGame().IsMultiplayer() || GetGame().IsClient() )
			{
				if (m_ParticleEfx)
					m_ParticleEfx.Stop();
			}
		}	
	}
	
	
	void Destroy_Wreck()
	{
		if (GetGame().IsServer()) 
		{
			ref array<Object> objects = new array<Object>;
			ref array<CargoBase> proxy = new array<CargoBase>;
		
			GetGame().GetObjectsAtPosition(this.GetPosition(), 15, objects, proxy);
						
			if ( objects ) //valid objects
			{
				for ( int i = 0; i < objects.Count(); i++ ) //loop all objects
				{
					Object obj = objects.Get(i); // get object
					
					if (obj.IsTree() || obj.IsBush() || obj.IsMan() ) //valid ptr check / sanity checks
						continue;
					
					if (obj.IsKindOf("Wreck_UH1Y"))
					{
						m_ShouldDeleteSmoke = true;
					}
					
					GetGame().ObjectDelete(obj);
					
					
				}
			}
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
}