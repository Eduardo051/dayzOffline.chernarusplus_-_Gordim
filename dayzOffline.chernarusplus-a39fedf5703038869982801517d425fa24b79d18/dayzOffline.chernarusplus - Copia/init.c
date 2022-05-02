static Object SpawnObject(string type, vector position, vector orientation)
{
	Object obj = GetGame().CreateObjectEx(type, position, ECE_SETUP | ECE_UPDATEPATHGRAPH | ECE_CREATEPHYSICS);
	if (!obj)
	{
		Error("[INIT]Falha ao Spawnar o objeto: " + type);
		return null;
	}

	obj.SetPosition(position);
	obj.SetOrientation(orientation);
	obj.SetOrientation(obj.GetOrientation());
	obj.SetFlags(EntityFlags.STATIC, false);
	obj.Update();
	obj.SetAffectPathgraph(true, false);
	if (obj.CanAffectPathgraph())
	{
		GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(GetGame().UpdatePathgraphRegionByObject, 100, false, obj);
	}
	return obj;
}

void main()
{

	bool loadTraderObjects = true;
	bool loadTraderNPCs = true;

	string MissionWorldName = "empty";
	GetGame().GetWorldName(MissionWorldName);

	if (MissionWorldName != "empty")
	{
		ExpansionObjectSpawnTools.FindMissionFiles("$CurrentDir:\\mpmissions\\Expansion." + MissionWorldName, loadTraderObjects, loadTraderNPCs);
	}

	// INIT ECONOMY--------------------------------------
	Hive ce = CreateHive();
	if (ce)
		ce.InitOffline();

	//DATE RESET AFTER ECONOMY INIT-------------------------
	int year, month, day, hour, minute;
	int reset_month = 6, reset_day = 20;
	GetGame().GetWorld().GetDate(year, month, day, hour, minute);

	if ((month == reset_month) && (day < reset_day))
	{
		GetGame().GetWorld().SetDate(year, reset_month, reset_day, hour, minute);
	}
	else
	{
		if ((month == reset_month + 1) && (day > reset_day))
		{
			GetGame().GetWorld().SetDate(year, reset_month, reset_day, hour, minute);
		}
		else
		{
			if ((month < reset_month) || (month > reset_month + 1))
			{
				GetGame().GetWorld().SetDate(year, reset_month, reset_day, hour, minute);
			}
		}
	}

	//EditorLoaderModule.ExportLootData = true;
	//GetCEApi().ExportProxyData(Vector(7500, GetGame().SurfaceY(7500, 7500), 7500), 20000);	

}
class CustomMission : MissionServer
{

 	ref array<string> Pallas = new array<string>;
	ref array<string> Vesta = new array<string>;

 	void CustomMission()
	{
		Pallas = new array<string>;
		Vesta = new array<string>;
		InitPlayerWhitelist();
	}
	void SetRandomHealth(EntityAI itemEnt)
	{
		if (itemEnt)
		{
			float rndHlt = Math.RandomFloat(0.75, 1);
			itemEnt.SetHealth01("", "", rndHlt);
		}
	}
	void addMags(PlayerBase player, string mag_type, int count)
	{
		if (count < 1)
			return;

		EntityAI mag;

		for (int i = 0; i < count; i++)
		{
			mag = player.GetInventory().CreateInInventory(mag_type);
		}
		//player.SetQuickBarEntityShortcut(mag, 2, true);
	}
	void InitPlayerWhitelist()
	{
		Pallas.Insert("ReplaceWithUniqueID");
		Pallas.Insert("ReplaceWithUniqueID");

		Vesta.Insert("oL76x7BjGlxS524X1KmWsW9C29H_p3zqYOHE_7D8TRw="); // Meta
		Vesta.Insert("ReplaceWithUniqueID");
	}
	override PlayerBase CreateCharacter(PlayerIdentity identity, vector pos, ParamsReadContext ctx, string characterName)
	{
		Entity playerEnt;
		playerEnt = GetGame().CreatePlayer(identity, characterName, pos, 0, "NONE");
		Class.CastTo(m_player, playerEnt);
		GetGame().SelectPlayer(identity, m_player);
		return m_player;
	}

	//-------------------------------------------------------|
	// Loudout Base |----------------------------------------|
	//-------------------------------------------------------|

	EntityAI LDT_Random(PlayerBase player)
	{
		ref TStringArray Comidas = {"Honey", "Zargoky", "ZagorkyChocolate", "ZagorkyPeanuts", "SaltySticks", "Crackers", "Chips", "SardinesCan", "Tunacan", "DogFoodcan", "CatFoodCan", "PorkCan", "LunchMeat", "Pajka", "Pate", "BrisketSpread", "Apple", "Plum", "Pear", "Banana", "Orange", "Kiwi", "Rice", "Marmalade", "PowderedMilk", "UnknowFoodCan", "TacticalBaconCan_Opened"};
		ref TStringArray Bebidas = {"Canteen", "WaterBottle", "SodaCan_Pipsi", "SodaCan_Cola", "SodaCan_Spite", "SodaCan_Kvass", "SodaCan_Fronta"};

		ref TStringArray Facas = {"CombatKnife", "HuntingKnife", "KukriKnife", "FangeKnife", "KithenKnife", "SteakKnife", "Machete"};
		ref TStringArray Luz = {"Chemlight_White", "Chemlight_Yellow", "Chemlight_Green", "Chemlight_Red"};

		ref TStringArray Oculos = {"SportGlasses_Blue", "", "", "SportGlasses_Black", "", "", "SportGlasses_Green", "", "", "SportGlasses_Orange", "", "", "AviatorGlasses"};
		ref TStringArray Botas = {"Joggingshoes_Black","Joggingshoes_Blue","Joggingshoes_Red","Joggingshoes_Violet","Joggingshoes_White","AthleticShoes_Blue","AthleticShoes_Grey","AthleticShoes_Brown","AthleticShoes_Green","AthleticShoes_Black"};
		ref TStringArray Camisa = {"TShirt_Green","TShirt_Blue","TShirt_Black","TShirt_Beige","TShirt_Red","TShirt_White","TShirt_Red","TShirt_Grey","TShirt_RedBlackStripes","TrackSuitJacket_Black","TrackSuitJacket_Blue","TrackSuitJacket_Green","TrackSuitJacket_LigthBlue","TrackSuitJacket_Red"};
		ref TStringArray Calca = {"TrackSuitPants_Black","TrackSuitPants_Blue","TrackSuitPants_Green","TrackSuitPants_Red","TrackSuitPants_LigthBlue","Breeches_Pink","Breeches_Red","Breeches_White","Breeches_Green","Breeches_Browncheck","Breeches_Blue","Breeches_Blackcheck","Breeches_Black","Breeches_Beige","Breeches_Beetcheck"};

		player.GetInventory().CreateInInventory(Oculos.GetRandomElement());
		player.GetInventory().CreateInInventory(Botas.GetRandomElement());
		player.GetInventory().CreateInInventory(Camisa.GetRandomElement());
		player.GetInventory().CreateInInventory(Calca.GetRandomElement());
		player.GetInventory().CreateInInventory("Iodine_Tincture");

		EntityAI Facas_i =	player.GetInventory().CreateInInventory(Facas.GetRandomElement());
		EntityAI Luz_i = 	player.GetInventory().CreateInInventory(Luz.GetRandomElement());
		EntityAI Comida_i =	player.GetInventory().CreateInInventory(Comidas.GetRandomElement());
		EntityAI Bebida_i =	player.GetInventory().CreateInInventory(Bebidas.GetRandomElement());
		EntityAI Rag_i = player.GetInventory().CreateInInventory("Rag");

		player.SetQuickBarEntityShortcut(Facas_i, 0, true);
		player.SetQuickBarEntityShortcut(Rag_i, 2, true);
		player.SetQuickBarEntityShortcut(Luz_i, 3, true);
		player.SetQuickBarEntityShortcut(Comida_i, 4, true);
		player.SetQuickBarEntityShortcut(Bebida_i, 5, true);

		return player;
	}
	EntityAI LDT_ADMIN(PlayerBase player)
	{
		ref TStringArray Comidas = {"Honey", "Zargoky", "ZagorkyChocolate", "ZagorkyPeanuts", "SaltySticks", "Crackers", "Chips", "SardinesCan", "Tunacan", "DogFoodcan", "CatFoodCan", "PorkCan", "LunchMeat", "Pajka", "Pate", "BrisketSpread", "Apple", "Plum", "Pear", "Banana", "Orange", "Kiwi", "Rice", "Marmalade", "PowderedMilk", "UnknowFoodCan", "TacticalBaconCan_Opened"};
		ref TStringArray Bebidas = {"Canteen", "WaterBottle", "SodaCan_Pipsi", "SodaCan_Cola", "SodaCan_Spite", "SodaCan_Kvass", "SodaCan_Fronta"};

		ref TStringArray Facas = {"CombatKnife", "HuntingKnife", "KukriKnife", "FangeKnife", "KithenKnife", "SteakKnife", "Machete"};
		ref TStringArray Luz = {"Chemlight_White", "Chemlight_Yellow", "Chemlight_Green", "Chemlight_Red"};

		ref TStringArray Oculos = {"SportGlasses_Blue", "", "", "SportGlasses_Black", "", "", "SportGlasses_Green", "", "", "SportGlasses_Orange", "", "", "AviatorGlasses"};
		ref TStringArray Botas = {"Joggingshoes_Black","Joggingshoes_Blue","Joggingshoes_Red","Joggingshoes_Violet","Joggingshoes_White","AthleticShoes_Blue","AthleticShoes_Grey","AthleticShoes_Brown","AthleticShoes_Green","AthleticShoes_Black"};
		ref TStringArray Camisa = {"TShirt_Green","TShirt_Blue","TShirt_Black","TShirt_Beige","TShirt_Red","TShirt_White","TShirt_Red","TShirt_Grey","TShirt_RedBlackStripes","TrackSuitJacket_Black","TrackSuitJacket_Blue","TrackSuitJacket_Green","TrackSuitJacket_LigthBlue","TrackSuitJacket_Red"};
		ref TStringArray Calca = {"TrackSuitPants_Black","TrackSuitPants_Blue","TrackSuitPants_Green","TrackSuitPants_Red","TrackSuitPants_LigthBlue","Breeches_Pink","Breeches_Red","Breeches_White","Breeches_Green","Breeches_Browncheck","Breeches_Blue","Breeches_Blackcheck","Breeches_Black","Breeches_Beige","Breeches_Beetcheck"};

		player.GetInventory().CreateInInventory(Oculos.GetRandomElement());
		player.GetInventory().CreateInInventory(Botas.GetRandomElement());
		player.GetInventory().CreateInInventory(Camisa.GetRandomElement());
		player.GetInventory().CreateInInventory(Calca.GetRandomElement());
		player.GetInventory().CreateInInventory("Iodine_Tincture");

		EntityAI Facas_i =	player.GetInventory().CreateInInventory(Facas.GetRandomElement());
		EntityAI Luz_i = 	player.GetInventory().CreateInInventory(Luz.GetRandomElement());
		EntityAI Comida_i =	player.GetInventory().CreateInInventory(Comidas.GetRandomElement());
		EntityAI Bebida_i =	player.GetInventory().CreateInInventory(Bebidas.GetRandomElement());
		EntityAI Rag_i = player.GetInventory().CreateInInventory("Rag");

		player.SetQuickBarEntityShortcut(Facas_i, 0, true);
		player.SetQuickBarEntityShortcut(Rag_i, 2, true);
		player.SetQuickBarEntityShortcut(Luz_i, 3, true);
		player.SetQuickBarEntityShortcut(Comida_i, 4, true);
		player.SetQuickBarEntityShortcut(Bebida_i, 5, true);

		return player;
	}
	EntityAI LDT_Meta(PlayerBase player)
	{
		ref TStringArray Comidas = {"Honey", "Zargoky", "ZagorkyChocolate", "ZagorkyPeanuts", "SaltySticks", "Crackers", "Chips", "SardinesCan", "Tunacan", "DogFoodcan", "CatFoodCan", "PorkCan", "LunchMeat", "Pajka", "Pate", "BrisketSpread", "Apple", "Plum", "Pear", "Banana", "Orange", "Kiwi", "Rice", "Marmalade", "PowderedMilk", "UnknowFoodCan", "TacticalBaconCan_Opened"};
		ref TStringArray Bebidas = {"Canteen", "WaterBottle", "SodaCan_Pipsi", "SodaCan_Cola", "SodaCan_Spite", "SodaCan_Kvass", "SodaCan_Fronta"};

		ref TStringArray Facas = {"CombatKnife", "HuntingKnife", "KukriKnife", "FangeKnife", "KithenKnife", "SteakKnife", "Machete"};
		ref TStringArray Luz = {"Chemlight_White", "Chemlight_Yellow", "Chemlight_Green", "Chemlight_Red"};

		ref TStringArray Oculos = {"SportGlasses_Blue", "", "", "SportGlasses_Black", "", "", "SportGlasses_Green", "", "", "SportGlasses_Orange", "", "", "AviatorGlasses"};
		ref TStringArray Botas = {"Joggingshoes_Black","Joggingshoes_Blue","Joggingshoes_Red","Joggingshoes_Violet","Joggingshoes_White","AthleticShoes_Blue","AthleticShoes_Grey","AthleticShoes_Brown","AthleticShoes_Green","AthleticShoes_Black"};
		ref TStringArray Camisa = {"TShirt_Green","TShirt_Blue","TShirt_Black","TShirt_Beige","TShirt_Red","TShirt_White","TShirt_Red","TShirt_Grey","TShirt_RedBlackStripes","TrackSuitJacket_Black","TrackSuitJacket_Blue","TrackSuitJacket_Green","TrackSuitJacket_LigthBlue","TrackSuitJacket_Red"};
		ref TStringArray Calca = {"TrackSuitPants_Black","TrackSuitPants_Blue","TrackSuitPants_Green","TrackSuitPants_Red","TrackSuitPants_LigthBlue","Breeches_Pink","Breeches_Red","Breeches_White","Breeches_Green","Breeches_Browncheck","Breeches_Blue","Breeches_Blackcheck","Breeches_Black","Breeches_Beige","Breeches_Beetcheck"};

		player.GetInventory().CreateInInventory(Oculos.GetRandomElement());
		player.GetInventory().CreateInInventory(Botas.GetRandomElement());
		player.GetInventory().CreateInInventory(Camisa.GetRandomElement());
		player.GetInventory().CreateInInventory(Calca.GetRandomElement());
		player.GetInventory().CreateInInventory("Iodine_Tincture");

		EntityAI Facas_i =	player.GetInventory().CreateInInventory(Facas.GetRandomElement());
		EntityAI Luz_i = 	player.GetInventory().CreateInInventory(Luz.GetRandomElement());
		EntityAI Comida_i =	player.GetInventory().CreateInInventory(Comidas.GetRandomElement());
		EntityAI Bebida_i =	player.GetInventory().CreateInInventory(Bebidas.GetRandomElement());
		EntityAI Rag_i = player.GetInventory().CreateInInventory("Rag");

		player.SetQuickBarEntityShortcut(Facas_i, 0, true);
		player.SetQuickBarEntityShortcut(Rag_i, 2, true);
		player.SetQuickBarEntityShortcut(Luz_i, 3, true);
		player.SetQuickBarEntityShortcut(Comida_i, 4, true);
		player.SetQuickBarEntityShortcut(Bebida_i, 5, true);

		return player;
	}
	//-------------------------------------------------------|
	// ARMAS |-----------------------------------------------|
	//-------------------------------------------------------|
	EntityAI SCND_MKII(PlayerBase player)
	{
		EntityAI SCND = player.GetInventory().CreateInInventory("MKII");
		SCND.GetInventory().CreateAttachment("Mag_MKII_10rnd");

		addMags(player, "Mag_MKII_10rnd", 1);

		player.SetQuickBarEntityShortcut(SCND, 1, true);
		return SCND;
	}
	EntityAI SCND_Makarov(PlayerBase player)
	{
		EntityAI SCND = player.GetInventory().CreateInInventory("MakarovIJ70");
		SCND.GetInventory().CreateAttachment("Mag_IJ70_8rnd");

		addMags(player, "Mag_IJ70_8rnd", 1);

		player.SetQuickBarEntityShortcut(SCND, 1, true);
		return SCND;
	}
	EntityAI SCND_Machado(PlayerBase player)
	{
		EntityAI SCND = player.GetInventory().CreateInInventory("Iceaxe");
		player.SetQuickBarEntityShortcut(SCND, 1, true);
		return SCND;
	}
	//============================================================================================
	override void StartingEquipSetup(PlayerBase player, bool clothesChosen)
	{
		player.RemoveAllItems();
		if (Pallas.Find(GetUserID(player)) != -1 || Pallas.Find(GetUserSteamID(player)) != -1)
		switch (Math.RandomInt(0, 3))
		{
			case 0:LDT_Random(player);SCND_MKII(player);break;
			case 1:LDT_Random(player);SCND_Makarov(player);break;
			case 2:LDT_Random(player);SCND_Machado(player);break;
		}
		else if (Vesta.Find(GetUserID(player)) != -1 || Vesta.Find(GetUserSteamID(player)) != -1)
		switch (Math.RandomInt(0, 3))
		{
			case 0:LDT_Meta(player);SCND_MKII(player);break;
			case 1:LDT_Meta(player);SCND_Makarov(player);break;
			case 2:LDT_Meta(player);SCND_Machado(player);break;
		}
		else
		switch (Math.RandomInt(0, 3))
		{
			case 0:LDT_Random(player);SCND_MKII(player);break;
			case 1:LDT_Random(player);SCND_Makarov(player);break;
			case 2:LDT_Random(player);SCND_Machado(player);break;
		}
	}
	//---------------------------------------------------------------
	string GetUserID(PlayerBase player)
	{
		if (player.GetIdentity())
			return player.GetIdentity().GetPlainId();

		return "OFFLINE";
	}
	string GetUserSteamID(PlayerBase player)
	{
		if (player.GetIdentity())
			return player.GetIdentity().GetId();

		return "OFFLINE";
	}
};
Mission CreateCustomMission(string path)
{
	return new CustomMission();
}

