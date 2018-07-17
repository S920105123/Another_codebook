void convex_hull(vector<Point> &ps, vector<Point> &hull) {
	// Find convex hull of ps, store in hull
	vector<Point> &stk=hull;
	stk.resize(ps.size()+1);
	sort(ps.begin(),ps.end()); // Using x to cmp, y secondary.
	int t=-1; // top
	for (int i=0;i<ps.size();i++) {
		// cross<-EPS -> count collinear, cross<EPS -> not
		while (t>=1&&(stk[t]-stk[t-1]).cross(ps[i]-stk[t])<EPS) t--;
		stk[++t]=ps[i];
	}
	int low=t;
	for (int i=ps.size()-2;i>=0;i--) {
		// cross<-EPS -> count collinear, cross<EPS -> not
		while (t>low&&(stk[t]-stk[t-1]).cross(ps[i]-stk[t])<EPS) t--;
		stk[++t]=ps[i];
	}
	stk.resize(t); // pop_back contain in this instruction
}
