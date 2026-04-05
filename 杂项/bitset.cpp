		for (int t=tmp._Find_first();t!=tmp.size();t=tmp._Find_next(t))
			ans[t] = i, nvis.reset(t);
