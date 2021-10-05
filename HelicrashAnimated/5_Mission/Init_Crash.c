modded class MissionServer
{
    void MissionServer()
    {	    
		if (GetGame().IsServer())  //run on the server
        {
		    g_HelicrashBase = null;
            GetHelicrashBase();
        }
    }
}

modded class MissionGameplay
{
    void MissionGameplay() //run on the server
    {
        if (GetGame().IsServer()) 
        {
            g_HelicrashBase = null;
            GetHelicrashBase();
        }	
    }
}