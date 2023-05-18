namespace PrefabManager {

	enum class Prefabs {

		CUBE,
		HARE,
		HAND,
		TAXI,
		BUTTERFLY,
		ROBOT,
		TREE,

	};

	inline Prefabs selectedPrefab = PrefabManager::Prefabs::CUBE; // default selection

	inline const char* prefabLabels[] = { "CUBE", "HARE", "HAND", "TAXI", "BUTTERFLY", "ROBOT", "TREE" };

	void Spawn(Prefabs P);

};