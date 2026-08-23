#include <bits/stdc++.h>
using namespace std;
#define ll double
ll a, b, c, d, e;
ll f(ll x)
{

  return a * x * x * x * x + b * x * x * x + c * x * x + d * x + e;
}

ll tmax()
{
  vector<ll> v;
  v.push_back(abs(b / a));
  v.push_back(abs(c / a));
  v.push_back(abs(d / a));
  v.push_back(abs(e / a));
  return 1 + *max_element(v.begin(), v.end());
}

void bisection(ll l, ll r)
{

  ll mid = (l + r) / 2;
  ll cnt = 1;
  while (fabs(mid - l) >= .0001)
  {
    cnt++;

    if (f(mid) * f(l) < 0)
      r = mid;
    else if (f(mid) * f(r) < 0)
      l = mid;
    else if (f(mid) == 0)
    {

      break;
    }
    mid = (l + r) / 2;
  }

  cout << "root:" << mid << endl;
  cout << "iteration:" << cnt << endl;

  return;
}

int main()
{
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
  ll T;
  cout << "Enter number of test cases: ";
  cout << endl;
  cin >> T;

  while (T--)
  {
    cout << "Enter coefficients a b c d e: " << endl;
    cin >> a >> b >> c >> d >> e;

    ll r = tmax();

    ll l = -r;

    cout << "Search interval:[" << l << " " << r << "]" << endl;
    while (l <= r)
    {
      ll d = l + 0.5;

      if (f(l) * f(d) < 0)
      {

        cout << "interval:[" << l << " " << d << "]" << endl;

        bisection(l, d);
      }
      l = d;
    }
  }
}
