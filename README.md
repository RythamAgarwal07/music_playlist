# 🎵 Music Recommendation & Playlist Management System (C++)

## 📌 Overview

This is a console-based music system built in C++ that allows users to register, login, manage playlists, play songs, and receive intelligent music recommendations.

The system also includes graph-based traversal (BFS & DFS), a greedy recommendation engine, and a gamified XP/achievement system to enhance user engagement.

User data is stored using file handling (`players.txt`) for persistence.

---

## 🚀 Features

### 👤 User Management
- User registration and login system
- Preference selection (3 favorite genres)
- Persistent user storage using file handling

### 🎧 Music System
- View available songs
- Play songs and earn XP
- Surprise random song feature

### 📂 Playlist System
- Create playlists (limited slots per user)
- Add songs to playlists
- View saved playlists with song details

### 🤖 Recommendation Engine
- Greedy algorithm-based recommendation
- Prioritizes:
  - Song popularity
  - User genre preferences

### 🌐 Graph-Based Exploration
- **BFS (Breadth First Search)**:
  - Explore related songs (same genre/artist connections)
- **DFS (Depth First Search)**:
  - Deep traversal of related songs

### 🏆 Gamification System
- XP points system
- Achievements such as:
  - First Play
  - Pop Lover
  - Playlist Creator
  - Smart Listener
  - Explorer
  - Deep Explorer
  - Beginner

---

## 🧠 Algorithms Used

- Greedy Algorithm → Recommendation system
- BFS → Queue-based song exploration
- DFS → Recursive song exploration
- File Handling → Persistent user data storage

---
