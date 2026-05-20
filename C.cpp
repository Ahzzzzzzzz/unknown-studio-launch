#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
const ll inf = 1e18;
const ll mod = 998244353;
const ld eps = 0.0000000001;
const ll N = 2e6+10;

ll kl(ll u){
    return 2*u
}

ll kr(ll u){
    return 2*u+1;
}

struct NODE{
    ll cnt,sum;
};

ll n;
vector<NODE> tr(4*N+10);

void push_up(ll u){
    tr[u].cnt = tr[kl(u)].cnt + tr[kr(u)].cnt;
    tr[u].sum = tr[kl(u)].sum + tr[kr(u)].sum;
}

void range_add(ll u , ll L , ll R , ll add , ll l , ll r){
    if(l > R || r < L) return;
    if(l >= L && r <= R){
        if(tr[u].cnt == 0 && add > 0) tr[u].sum++;
        tr[u].cnt += add;
        return;
    }

    ll mid = l + (r-l)/2;
    range_add(kl(u),L,R,add,l,mid);
    range_add(kr(u),L,R,add,mid+1,r);
    push_up(u);
}

ll range_cnt(ll u , ll L , ll R , ll l , ll r){
    if(l > R || r < L) return 0;
    if(l >= L && r <= R){
        return tr[u].cnt;
    }

    ll mid = l + (r-l)/2;
    return range_cnt(kl(u),L,R,l,mid) + range_cnt(kr(u),L,R,mid+1,r);
}

ll range_sum(ll u , ll L , ll R , ll l , ll r){
    if(l > R || r < L) return 0;
    if(l >= L && r <= R){
        return tr[u].sum;
    }

    ll mid = l + (r-l)/2;
    return range_sum(kl(u),L,R,l,mid) + range_sum(kr(u),L,R,mid+1,r);
}

ll find_mn(ll u , ll l , ll r){
    if(l == r) return l;

    ll mid = l + (r-l)/2;
    if(tr[kl(u)].cnt > 0) return find_mn(kl(u),l,mid);
    if(tr[kr(u)].cnt > 0) return find_mn(kr(u),mid+1,r);
    return -1;
}

ll find_mx(ll u , ll l , ll r){
    if(l == r) return l;

    ll mid = l + (r-l)/2;
    if(tr[kr(u)].cnt > 0) return find_mx(kr(u),mid+1,r);
    if(tr[kl(u)].cnt > 0) return find_mx(kl(u),l,mid);
    return -1;
}

void build(ll u , ll l , ll r){
    tr[u].cnt = tr[u].sum = 0;
    if(l == r) return;
    ll mid = l + (r-l)/2;
    build(kl(u),l,mid);
    build(kr(u),mid+1,r);
    push_up(u);
}

void init(){
    build(1,1,n);
}

void solve(){
    cin >> n;
    init();
    vector<vector<ll>> mp(n+1);
    for(ll i = 1 ; i <= n ; i ++){
        ll x,y; cin >> x >> y;
        mp[y].push_back(x);
        range_add(1,x,x,1,1,n);
    }

    ll ans = 0 , up = 0;
    ll xl1 = inf , xr1 = -inf , xl2 = inf , xr2 = -inf;
    for(ll y = 1 ; y <= n ; y ++){
        if(mp[y].size() == 0) continue;
        for(ll j = 0 ; j < mp[y].size() ; j ++){
            ll x = mp[y][j];
            xl1 = min(xl1 , x); xr1 = max(xr1 , x);
            range_add(1,x,x,-1,1,n);
            up++;
        }

        if(up >= 2 && tr[1].cnt >= 2){
            xl2 = find_mn(1,1,n) , xr2 = find_mx(1,1,n);
            // cerr << xl1 << ' ' << xr1 << ' ' << xl2 << ' ' << xr2 << '\n'; 
            ll l = max(xl1 , xl2) , r = min(xr1 , xr2);
            ans += max(0ll,range_sum(1,l,r,1,n)-1);
            // cerr << l << ' ' << r << '\n';
            // cerr << range_sum(1,l,r,1,n) << '\n';
            // cerr << '\n';
        }
    }

    cout << ans << '\n';
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	ll t; t = 1;
    cin >> t;
	while(t--){
		solve();
	}

    return 0;
} 
 
