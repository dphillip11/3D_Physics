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
		VOID

	};

	inline Prefabs selectedPrefab = PrefabManager::Prefabs::CUBE; // default selection

	inline const char* prefabLabels[] = { "CUBE", "HARE", "HAND", "TAXI", "BUTTERFLY", "ROBOT", "TREE" ,"AIRPLANE", "VOID" };

	void Spawn(Prefabs P);

};