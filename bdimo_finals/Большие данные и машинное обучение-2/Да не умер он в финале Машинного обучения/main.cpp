#include <bits/stdc++.h>
#define endl '\n'

using namespace std;
int const L = 2e7;
double likerate[L], topicrate[L];
int watched[L], watched_t[L];
char ans[L];
struct ask {
    int topicid;
    int userid;
    int ind;
    double like;
};

char answer[L];

bool cmp(ask x, ask y) {
    return x.like > y.like;
}

long double avg = 0;

int main()
{
    freopen("train.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    long long n, m;
    cin >> n >> m;
    for (long long i = 0; i != m; ++i) {
        long long a, b;
        char c;
        cin >> a >> b >> c;
        if (c == 'L') {
            ++likerate[b];
            ++topicrate[a];
        }
        answer[i] = c;
        ++watched[b];
        ++watched_t[a];
    }
    for (long long i = 0; i != m; ++i) {
        if (watched[i] != 0) {
            likerate[i] /= (double)watched[i];
        } else {
            likerate[i] = 0.5;
        }
        if(watched_t[i] != 0){
            topicrate[i] /= watched_t[i];
        } else {
            topicrate[i] = 1;
        }
        if(likerate[i] > 0.9) {
            likerate[i] -= 0.15;
        }
        likerate[i] = 1 - likerate[i];
        //topicrate[i] = 1 - topicrate[i];
    }
    freopen("test.txt", "r", stdin);
    vector<ask> q;
    cin >> n >> n;
    for (int i = 0; i != n; ++i) {
        ask a;
        cin >> a.topicid >> a.userid;
        a.ind = i;
        a.like = pow(likerate[a.userid], 9) * topicrate[a.topicid];
        avg += a.like;
        q.push_back(a);
    }
    avg /= n;
    sort(q.begin(), q.end(), cmp);
    for (int i = 0; i != n; ++i) {
        if (i < n * 0.528) {
            ans[q[i].ind] = 'L';
        } else {
            ans[q[i].ind] = 'D';
        }
    }
    freopen("out.txt", "w", stdout);
    for (int i = 0; i != n; ++i) {
        cout << ans[i] << endl;
    }
}
