////////////////////////////////////////////////////////////////////
//DeRap: Helicrash_Models\config.bin
//Produced from mikero's Dos Tools Dll version 7.79
//https://mikero.bytex.digital/Downloads
//'now' is Sat Sep 26 21:15:19 2020 : 'file' last modified on Sat Sep 26 21:14:19 2020
////////////////////////////////////////////////////////////////////

#define _ARMA_

class CfgPatches
{
	class Helicrash_Models
	{
		units[] = {};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = {"DZ_Data"};
	};
};
class CfgVehicles
{
	class HouseNoDestruct;
	class Roadflare;
	class Container_Base;
	class Inventory_Base;
	class Rotation;
	class ExpansionUH: HouseNoDestruct
	{
		scope = 1;
		model = "\Helicrash_Models\UH1Y.p3d";
		class AnimationSources
		{
			class rotor
			{
				source = "user";
				animPeriod = 0.025;
				initPhase = 0;
			};
			class rearrotor
			{
				source = "user";
				animPeriod = 0.025;
				initPhase = 0;
			};
			class hiderotor
			{
				source = "user";
				animPeriod = 0.0009999999;
				initPhase = 0;
			};
			class hiderotorblur
			{
				source = "user";
				animPeriod = 0.0009999999;
				initPhase = 0;
			};
			class cyclicForward
			{
				source = "user";
				animPeriod = 0.25;
				initPhase = 0;
			};
			class cyclicAside
			{
				source = "user";
				animPeriod = 0.25;
				initPhase = 0;
			};
			class door_pilot
			{
				source = "user";
				animPeriod = 0.5;
				initPhase = 0;
			};
			class door_copilot
			{
				source = "user";
				animPeriod = 0.5;
				initPhase = 0;
			};
			class uh1hdoor_1_1
			{
				source = "user";
				animPeriod = 0.5;
				initPhase = 0;
			};
			class uh1hdoor_1_2
			{
				source = "user";
				animPeriod = 0.5;
				initPhase = 0;
			};
		};
	};
	class ExpansionUH_Crash: HouseNoDestruct
	{
		scope = 1;
		model = "\Helicrash_Models\UH1Y.p3d";
	};
	class ExpansionMi8: HouseNoDestruct
	{
		scope = 1;
		model = "\Helicrash_Models\Mi_8AMT.p3d";
		class AnimationSources
		{
			class rotor
			{
				source = "user";
				animPeriod = 0.025;
				initPhase = 0;
			};
			class RotorWithoutBlurAnimation
			{
				source = "user";
				animPeriod = 0.025;
				initPhase = 0;
				sourceAddress = "loop";
			};
			class rearrotor
			{
				source = "user";
				animPeriod = 0.025;
				initPhase = 0;
			};
			class hiderotor
			{
				source = "user";
				animPeriod = 0.0009999999;
				initPhase = 0;
			};
			class hiderotorblur
			{
				source = "user";
				animPeriod = 0.0009999999;
				initPhase = 0;
			};
			class cyclicForward
			{
				source = "user";
				animPeriod = 0.25;
				initPhase = 0;
			};
			class cyclicAside
			{
				source = "user";
				animPeriod = 0.25;
				initPhase = 0;
			};
			class door_pilot
			{
				source = "user";
				animPeriod = 0.5;
				initPhase = 0;
			};
			class door_copilot
			{
				source = "user";
				animPeriod = 0.5;
				initPhase = 0;
			};
			class uh1hdoor_1_1
			{
				source = "user";
				animPeriod = 0.5;
				initPhase = 0;
			};
			class uh1hdoor_1_2
			{
				source = "user";
				animPeriod = 0.5;
				initPhase = 0;
			};
		};
	};
	class ExpansionMi8_Crash: HouseNoDestruct
	{
		scope = 1;
		model = "\Helicrash_Models\Mi_8AMT.p3d";
	};
};
class CfgSoundShaders
{
	class baseCharacter_SoundShader;
	class Expansion_Mi8_Base_Int_SoundShader
	{
		range = 1000;
	};
	class Expansion_Mi8_Base_Ext_SoundShader
	{
		range = 1000;
	};
	class Expansion_Mi8_Loop_Int_SoundShader: Expansion_Mi8_Base_Int_SoundShader
	{
		samples[] = {{"Helicrash_Models\Sounds\Expansion_Mi8_Loop_Int",1}};
		range = 1000;
	};
	class Expansion_Mi8_Loop_Ext_SoundShader: Expansion_Mi8_Base_Ext_SoundShader
	{
		samples[] = {{"Helicrash_Models\Sounds\Expansion_Mi8_Loop_Ext",1}};
		range = 1000;
	};
	class Expansion_Mi8_Rotor_Int_SoundShader: Expansion_Mi8_Base_Int_SoundShader
	{
		samples[] = {{"Helicrash_Models\Sounds\Expansion_Mi8_Rotor_Int",1}};
		range = 1000;
	};
	class Expansion_Mi8_Rotor_Ext_SoundShader: Expansion_Mi8_Base_Ext_SoundShader
	{
		samples[] = {{"Helicrash_Models\Sounds\Expansion_Mi8_Rotor_Ext",1}};
		range = 1000;
	};
};
class CfgSoundSets
{
	class baseCharacter_SoundSet;
	class Expansion_Mi8_Base_Ext_SoundSet
	{
		sound3DProcessingType = "Vehicle_Ext_3DProcessingType";
		distanceFilter = "softVehiclesDistanceFreqAttenuationFilter";
		volumeCurve = "vehicleEngineAttenuationCurve";
		volumeFactor = 1;
		occlusionFactor = 0;
		obstructionFactor = 0;
		spatial = 1;
		loop = 1;
		positionOffset[] = {0,0,0};
	};
	class Expansion_Mi8_Base_Int_SoundSet
	{
		sound3DProcessingType = "Vehicle_Int_3DProcessingType";
		distanceFilter = "softVehiclesDistanceFreqAttenuationFilter";
		volumeCurve = "vehicleEngineAttenuationCurve";
		volumeFactor = 1;
		occlusionFactor = 0;
		obstructionFactor = 0;
		spatial = 1;
		loop = 1;
		positionOffset[] = {0,0,0};
	};
	class Expansion_Mi8_Loop_Int_SoundSet: Expansion_Mi8_Base_Int_SoundSet
	{
		soundShaders[] = {"Expansion_Mi8_Loop_Int_SoundShader"};
		volumeFactor = 1;
	};
	class Expansion_Mi8_Loop_Ext_SoundSet: Expansion_Mi8_Base_Ext_SoundSet
	{
		soundShaders[] = {"Expansion_Mi8_Loop_Ext_SoundShader"};
		volumeFactor = 1;
	};
	class Expansion_Mi8_Rotor_Int_SoundSet: Expansion_Mi8_Base_Int_SoundSet
	{
		soundShaders[] = {"Expansion_Mi8_Rotor_Int_SoundShader"};
		volumeFactor = 1;
	};
	class Expansion_Mi8_Rotor_Ext_SoundSet: Expansion_Mi8_Base_Ext_SoundSet
	{
		soundShaders[] = {"Expansion_Mi8_Rotor_Ext_SoundShader"};
		volumeFactor = 1;
	};
};
class CfgSounds
{
	class default
	{
		name = "";
		titles[] = {};
	};
	class Expansion_Mi8_Base_Loop_Int: default
	{
		sound[] = {"\Helicrash_Models\Sounds\Expansion_Mi8_Rotor_Ext",1,1,1000};
	};
	class Explosion_Init: default
	{
		sound[] = {"\Helicrash_Models\Sounds\fuel1",1,1,1000};
	};
	class Explosion_Init_Ground: default
	{
		sound[] = {"\Helicrash_Models\Sounds\satch2",1,1,1000};
	};
};
