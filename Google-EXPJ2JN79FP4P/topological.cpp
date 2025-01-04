
https://leetcode.com/problems/find-all-possible-recipes-from-given-supplies/



class Solution {
public:
    bool dfs(string recipe, unordered_map<string, vector<string>> &adj, unordered_set<string> &visited, unordered_set<string> &supplies, unordered_set<string> &rawIngredients){
        
        if(supplies.find(recipe) != supplies.end())
            return true;

        if(visited.find(recipe) != visited.end())
            return false;

        visited.insert(recipe);

        for(auto &neigh : adj[recipe]){
            if(!dfs(neigh, adj, visited, supplies, rawIngredients))
                return false; 
        }

        visited.erase(recipe);

        if(rawIngredients.find(recipe) != rawIngredients.end() && supplies.find(recipe) == supplies.end())
            return false;

        supplies.insert(recipe);

        return true;

    }



    vector<string> findAllRecipes(vector<string>& recipes, vector<vector<string>>& ingredients, vector<string>& supplies) {
        
	int n = recipes.size();
	unordered_map<string, vector<string>> adj;


	unordered_set<string> rec(recipes.begin(), recipes.end());
	unordered_set<string> rawIngredients;
    vector<string> res;
	unordered_set<string> visited;
    unordered_set<string> sup(supplies.begin(), supplies.end());

	for(int i = 0; i < n; i++){
		for(auto & ingredient : ingredients[i]){
            adj[recipes[i]].push_back(ingredient);
            if(rec.find(ingredient) == rec.end())
                rawIngredients.insert(ingredient);
        }	
	}

 	for(int i = 0; i < n; i++){
        if(dfs(recipes[i], adj, visited, sup, rawIngredients))
            res.push_back(recipes[i]);	
	}
    return res;
    }

};