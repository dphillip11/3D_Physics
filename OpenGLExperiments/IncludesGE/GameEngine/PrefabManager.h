namespace PrefabManager {

	enum class Prefabs {

		CUBE,
		HARE,
		HAND,
		TAXI,
		BUTTERFLY,
		ROBOT,
		TREE,
		AIRPLANE,
		SPHERE,
		VOID

	};

	inline Prefabs selectedPrefab = PrefabManager::Prefabs::CUBE; // default selection

	inline const char* prefabLabels[] = { "CUBE", "HARE", "HAND", "TAXI", "BUTTERFLY", "ROBOT", "TREE" ,"AIRPLANE","SPHERE", "VOID" };

	int Spawn(Prefabs P);

	void SpawnLevel();

};