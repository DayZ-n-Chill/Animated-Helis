////////////////////////////////////////////////////////////////////
//DeRap: HelicrashAnimated\config.bin
//Produced from mikero's Dos Tools Dll version 8.26
//https://mikero.bytex.digital/Downloads
//'now' is Tue Oct 05 10:19:03 2021 : 'file' last modified on Wed Dec 31 18:00:01 1969
////////////////////////////////////////////////////////////////////

#define _ARMA_

class CfgPatches
{
	class HelicrashAnimated
	{
		units[] = {};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = {"DZ_Data","DZ_Gear_Consumables","DZ_Gear_Camping"};
	};
};
class CfgMods
{
	class HelicrashAnimated
	{
		dir = "HelicrashAnimated";
		picture = "";
		action = "";
		hideName = 0;
		hidePicture = 1;
		name = "HelicrashAnimated";
		credits = "Dylan";
		author = "Dylan";
		authorID = "";
		extra = 0;
		type = "mod";
		dependencies[] = {"Game","World","Mission"};
		class defs
		{
			class gameScriptModule
			{
				value = "";
				files[] = {"HelicrashAnimated/3_Game"};
			};
			class worldScriptModule
			{
				value = "";
				files[] = {"HelicrashAnimated/4_World"};
			};
			class missionScriptModule
			{
				value = "";
				files[] = {"HelicrashAnimated/5_Mission"};
			};
		};
	};
};
