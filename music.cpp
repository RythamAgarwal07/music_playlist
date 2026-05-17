#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <cstdlib>
#include <ctime>
using namespace std;

const int MAX_USERS = 10, MAX_SONGS = 10, MAX_PLAYLISTS = 3, MAX_PLAYLIST_SONGS = 10, MAX_ACH = 10;

struct Song {
    int id, popularity;
    string title, genre, artist;
};

struct Playlist {
    string name;
    int songs[MAX_PLAYLIST_SONGS], count = 0;
};

struct User {
    string name, email, password, pref1, pref2, pref3;
    int xp = 0, songsPlayed = 0, popCount = 0, greedyCount = 0, bfsCount = 0, dfsCount = 0, playlistCount = 0;
    string achievements[MAX_ACH];
    int achCount = 0;
    Playlist playlists[MAX_PLAYLISTS];
};

User users[MAX_USERS];
Song songs[MAX_SONGS];
int userCount = 0, songCount = 0;

void line() { cout << "--------------------------------------------------\n"; }

void addAchievement(User &u, string ach, bool show = true) {
    for (int i = 0; i < u.achCount; i++) if (u.achievements[i] == ach) return;
    if (u.achCount < MAX_ACH) {
        u.achievements[u.achCount++] = ach;
        if (show) cout << "\nAchievement Unlocked: " << ach << "\n";
    }
}

void checkAchievements(User &u, bool show = true) {
    if (u.songsPlayed >= 1) addAchievement(u, "First Play", show);
    if (u.popCount >= 5) addAchievement(u, "Pop Lover", show);
    if (u.playlistCount >= 1) addAchievement(u, "Playlist Creator", show);
    if (u.greedyCount >= 3) addAchievement(u, "Smart Listener", show);
    if (u.bfsCount >= 1) addAchievement(u, "Explorer", show);
    if (u.dfsCount >= 1) addAchievement(u, "Deep Explorer", show);
    if (u.xp >= 50) addAchievement(u, "Beginner", show);
}

bool isPreferred(User &u, string genre) {
    return genre == u.pref1 || genre == u.pref2 || genre == u.pref3;
}

int findSong(int id) {
    for (int i = 0; i < songCount; i++) if (songs[i].id == id) return i;
    return -1;
}

bool related(Song a, Song b) {
    return a.id != b.id && (a.genre == b.genre || a.artist == b.artist);
}

bool songInPlaylist(Playlist &p, int id) {
    for (int i = 0; i < p.count; i++) if (p.songs[i] == id) return true;
    return false;
}

void saveUsers() {
    ofstream fout("players.txt");
    for (int i = 0; i < userCount; i++) {
        fout << users[i].name << "|"
             << users[i].email << "|"
             << users[i].password << "|"
             << users[i].pref1 << "|"
             << users[i].pref2 << "|"
             << users[i].pref3 << "|"
             << users[i].xp << "|"
             << users[i].songsPlayed << "|"
             << users[i].popCount << "|"
             << users[i].greedyCount << "|"
             << users[i].bfsCount << "|"
             << users[i].dfsCount << "|"
             << users[i].playlistCount << "\n";
    }
}

void resetPlaylists(User &u) {
    for (int i = 0; i < MAX_PLAYLISTS; i++) u.playlists[i].count = 0;
}

void loadUsers() {
    ifstream fin("players.txt");
    if (!fin.is_open()) return;

    string s;
    while (getline(fin, s) && userCount < MAX_USERS) {
        string part[13], temp = "";
        int k = 0;

        for (int i = 0; i < (int)s.size(); i++) {
            if (s[i] == '|') part[k++] = temp, temp = "";
            else temp += s[i];
        }
        part[k] = temp;

        User &u = users[userCount];
        u.name = part[0]; u.email = part[1]; u.password = part[2];
        u.pref1 = part[3]; u.pref2 = part[4]; u.pref3 = part[5];
        u.xp = stoi(part[6]); u.songsPlayed = stoi(part[7]); u.popCount = stoi(part[8]);
        u.greedyCount = stoi(part[9]); u.bfsCount = stoi(part[10]); u.dfsCount = stoi(part[11]);
        u.playlistCount = stoi(part[12]); u.achCount = 0;
        resetPlaylists(u);
        checkAchievements(u, false);
        userCount++;
    }
}

void addDefaultUsers() {
    if (userCount > 0) return;

    users[0] = {"Aarav","aarav@gmail.com","1234","Pop","Rock","EDM",60,5,5,2,1,0,1};
    resetPlaylists(users[0]);
    checkAchievements(users[0], false);
    userCount++;

    users[1] = {"Meera","meera@gmail.com","1234","Bollywood","Pop","Lo-fi",30,2,1,1,0,0,0};
    resetPlaylists(users[1]);
    checkAchievements(users[1], false);
    userCount++;

    saveUsers();
}

void addSongs() {
    songs[0] = {1,95,"Blinding Lights","Pop","The Weeknd"};
    songs[1] = {2,90,"Believer","Rock","Imagine Dragons"};
    songs[2] = {3,93,"Kesariya","Bollywood","Arijit Singh"};
    songs[3] = {4,89,"Levitating","Pop","Dua Lipa"};
    songs[4] = {5,92,"Shape of You","Pop","Ed Sheeran"};
    songs[5] = {6,86,"Faded","EDM","Alan Walker"};
    songs[6] = {7,84,"Closer","EDM","Chainsmokers"};
    songs[7] = {8,87,"Rockstar","Hip-Hop","Post Malone"};
    songs[8] = {9,82,"Until I Found You","Lo-fi","Stephen Sanchez"};
    songs[9] = {10,85,"Numb","Rock","Linkin Park"};
    songCount = 10;
}

void registerUser() {
    if (userCount >= MAX_USERS) {
        cout << "User limit reached\n";
        return;
    }

    User &u = users[userCount];
    cout << "Enter name: "; cin >> u.name;
    cout << "Enter email: "; cin >> u.email;

    for (int i = 0; i < userCount; i++) {
        if (users[i].email == u.email) {
            cout << "Email already exists\n";
            return;
        }
    }

    cout << "Enter password: "; cin >> u.password;
    cout << "Choose 3 preferred genres:\n1.Pop 2.Rock 3.Bollywood 4.EDM 5.Hip-Hop 6.Lo-fi\n";

    int c1, c2, c3;
    string g[6] = {"Pop", "Rock", "Bollywood", "EDM", "Hip-Hop", "Lo-fi"};
    cin >> c1 >> c2 >> c3;

    u.pref1 = g[c1 - 1];
    u.pref2 = g[c2 - 1];
    u.pref3 = g[c3 - 1];
    u.xp = u.songsPlayed = u.popCount = u.greedyCount = u.bfsCount = u.dfsCount = u.playlistCount = u.achCount = 0;
    resetPlaylists(u);

    userCount++;
    saveUsers();
    cout << "Profile created successfully\n";
}

int loginUser() {
    string email, password;
    cout << "Enter email: "; cin >> email;
    cout << "Enter password: "; cin >> password;

    for (int i = 0; i < userCount; i++) {
        if (users[i].email == email && users[i].password == password) {
            cout << "Welcome " << users[i].name << "\n";
            return i;
        }
    }
    cout << "Invalid login\n";
    return -1;
}

void viewSongs() {
    line();
    cout << "ID   Title                 Genre\n";
    line();
    for (int i = 0; i < songCount; i++)
        cout << songs[i].id << "    " << songs[i].title << "    " << songs[i].genre << "\n";
    line();
}

void playSong(User &u) {
    int id;
    cout << "Enter song id: ";
    cin >> id;

    int i = findSong(id);
    if (i == -1) {
        cout << "Song not found\n";
        return;
    }

    cout << "Now Playing: " << songs[i].title << " - " << songs[i].artist << "\n";
    u.songsPlayed++;
    u.xp += 10;
    if (songs[i].genre == "Pop") u.popCount++;
    checkAchievements(u);
    saveUsers();
}

void createPlaylist(User &u) {
    if (u.playlistCount >= MAX_PLAYLISTS) {
        cout << "Playlist limit reached\n";
        return;
    }

    cout << "Enter playlist name: ";
    cin >> u.playlists[u.playlistCount].name;
    u.playlists[u.playlistCount].count = 0;
    u.playlistCount++;
    u.xp += 5;

    checkAchievements(u);
    saveUsers();
    cout << "Playlist created\n";
}

void addSongToPlaylist(User &u) {
    if (u.playlistCount == 0) {
        cout << "Create playlist first\n";
        return;
    }

    for (int i = 0; i < u.playlistCount; i++) cout << i + 1 << ". " << u.playlists[i].name << "\n";

    int p, id;
    cout << "Choose playlist: "; cin >> p;
    cout << "Enter song id: "; cin >> id;

    if (p < 1 || p > u.playlistCount) {
        cout << "Invalid playlist\n";
        return;
    }

    int i = findSong(id);
    if (i == -1) {
        cout << "Song not found\n";
        return;
    }

    Playlist &pl = u.playlists[p - 1];
    if (songInPlaylist(pl, id)) {
        cout << "Song already in playlist\n";
        return;
    }
    if (pl.count >= MAX_PLAYLIST_SONGS) {
        cout << "Playlist full\n";
        return;
    }

    pl.songs[pl.count++] = id;
    cout << "Song added\n";
}

void viewPlaylists(User &u) {
    if (u.playlistCount == 0) {
        cout << "No playlists\n";
        return;
    }

    for (int i = 0; i < u.playlistCount; i++) {
        cout << "\nPlaylist: " << u.playlists[i].name << "\n";
        if (u.playlists[i].count == 0) cout << "Empty\n";
        else {
            for (int j = 0; j < u.playlists[i].count; j++) {
                int k = findSong(u.playlists[i].songs[j]);
                if (k != -1) cout << "- " << songs[k].title << "\n";
            }
        }
    }
}

void greedyRecommend(User &u) {
    int best = -1, bestScore = -1;

    for (int i = 0; i < songCount; i++) {
        int score = songs[i].popularity + (isPreferred(u, songs[i].genre) ? 50 : 0);
        if (score > bestScore) bestScore = score, best = i;
    }

    if (best == -1) return;

    cout << "Recommended Song: " << songs[best].title << " - " << songs[best].genre << "\n";
    u.greedyCount++;
    u.xp += 5;

    if (isPreferred(u, songs[best].genre)) addAchievement(u, "Perfect Match");
    checkAchievements(u);
    saveUsers();
}

void bfsSongs(User &u) {
    int id;
    cout << "Enter starting song id: ";
    cin >> id;

    int start = findSong(id);
    if (start == -1) {
        cout << "Song not found\n";
        return;
    }

    int visited[MAX_SONGS] = {0};
    queue<int> q;
    visited[start] = 1;
    q.push(start);

    cout << "BFS:\n";
    while (!q.empty()) {
        int cur = q.front(); q.pop();
        cout << songs[cur].title << "\n";

        for (int i = 0; i < songCount; i++) {
            if (!visited[i] && related(songs[cur], songs[i])) {
                visited[i] = 1;
                q.push(i);
            }
        }
    }

    u.bfsCount++;
    u.xp += 5;
    checkAchievements(u);
    saveUsers();
}

void dfsHelper(int cur, int visited[]) {
    visited[cur] = 1;
    cout << songs[cur].title << "\n";

    for (int i = 0; i < songCount; i++)
        if (!visited[i] && related(songs[cur], songs[i]))
            dfsHelper(i, visited);
}

void dfsSongs(User &u) {
    int id;
    cout << "Enter starting song id: ";
    cin >> id;

    int start = findSong(id);
    if (start == -1) {
        cout << "Song not found\n";
        return;
    }

    int visited[MAX_SONGS] = {0};
    cout << "DFS:\n";
    dfsHelper(start, visited);

    u.dfsCount++;
    u.xp += 5;
    checkAchievements(u);
    saveUsers();
}

void viewUserAchievements(User &u) {
    if (u.achCount == 0) {
        cout << "No achievements yet\n";
        return;
    }
    for (int i = 0; i < u.achCount; i++) cout << "- " << u.achievements[i] << "\n";
}

void surpriseSong(User &u) {
    int r = rand() % songCount;
    cout << "Surprise Song: " << songs[r].title << "\n";

    u.songsPlayed++;
    u.xp += 5;
    if (songs[r].genre == "Pop") u.popCount++;

    checkAchievements(u);
    saveUsers();
}

int main() {
    srand(time(0));
    loadUsers();
    addDefaultUsers();
    addSongs();

    int current = -1, choice;

    while (true) {
        if (current == -1) {
            line();
            cout << "1.Register\n2.Login\n3.Exit\n";
            line();
            cin >> choice;

            if (choice == 1) registerUser();
            else if (choice == 2) current = loginUser();
            else if (choice == 3) break;
            else cout << "Invalid choice\n";
        } else {
            line();
            cout << "1.View Songs\n2.Play Song\n3.Create Playlist\n4.Add Song to Playlist\n5.View Playlists\n";
            cout << "6.Greedy Recommendation\n7.BFS\n8.DFS\n9.View Achievements\n10.Surprise Song\n11.Logout\n12.Exit\n";
            line();
            cin >> choice;

            if (choice == 1) viewSongs();
            else if (choice == 2) playSong(users[current]);
            else if (choice == 3) createPlaylist(users[current]);
            else if (choice == 4) addSongToPlaylist(users[current]);
            else if (choice == 5) viewPlaylists(users[current]);
            else if (choice == 6) greedyRecommend(users[current]);
            else if (choice == 7) bfsSongs(users[current]);
            else if (choice == 8) dfsSongs(users[current]);
            else if (choice == 9) viewUserAchievements(users[current]);
            else if (choice == 10) surpriseSong(users[current]);
            else if (choice == 11) current = -1;
            else if (choice == 12) break;
            else cout << "Invalid choice\n";
        }
    }
    return 0;
}