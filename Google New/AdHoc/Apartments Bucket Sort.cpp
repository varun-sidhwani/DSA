https://leetcode.com/discuss/interview-question/5809110/Google-L3-USA-Onsite-interview-questions

struct Apartment {
    int apt_id;       // Apartment ID
    int num_bedrooms; // Number of bedrooms
};

struct Person {
    string name;      // Intern's name
    bool wants_housemates; // Preference: true if they want to share
};

unordered_map<int, vector<string>> assignApartments(vector<Apartment>& apartments, vector<Person>& interns, int max_bedrooms) {
    // Output map: Apartment ID -> List of intern names
    unordered_map<int, vector<string>> apartments_to_tenants;

    // Separate interns based on preferences
    vector<Person> sharing_interns, solo_interns;
    for (const auto& intern : interns) {
        if (intern.wants_housemates) {
            sharing_interns.push_back(intern);
        } else {
            solo_interns.push_back(intern);
        }
    }

    // Bucket Sort Apartments by number of bedrooms
    vector<vector<Apartment>> buckets(max_bedrooms + 1); // Buckets from 0 to max_bedrooms
    for (const auto& apartment : apartments) {
        buckets[apartment.num_bedrooms].push_back(apartment);
    }

    // Assign single-bedroom apartments to solo interns first
    for (const auto& apartment : buckets[1]) { // Bucket for 1-bedroom apartments
        if (!solo_interns.empty()) {
            apartments_to_tenants[apartment.apt_id].push_back(solo_interns.back().name);
            solo_interns.pop_back();
        }
    }

    // Assign multi-bedroom apartments to sharing interns
    for (int bedrooms = 2; bedrooms <= max_bedrooms; bedrooms++) { // Buckets for multi-bedroom apartments
        for (const auto& apartment : buckets[bedrooms]) {
            for (int i = 0; i < bedrooms && !sharing_interns.empty(); i++) {
                apartments_to_tenants[apartment.apt_id].push_back(sharing_interns.back().name);
                sharing_interns.pop_back();
            }
        }
    }

    // Assign remaining interns to any available apartments
    for (int bedrooms = 1; bedrooms <= max_bedrooms; bedrooms++) {
        for (const auto& apartment : buckets[bedrooms]) {
            while (!solo_interns.empty() && apartments_to_tenants[apartment.apt_id].size() < apartment.num_bedrooms) {
                apartments_to_tenants[apartment.apt_id].push_back(solo_interns.back().name);
                solo_interns.pop_back();
            }
            while (!sharing_interns.empty() && apartments_to_tenants[apartment.apt_id].size() < apartment.num_bedrooms) {
                apartments_to_tenants[apartment.apt_id].push_back(sharing_interns.back().name);
                sharing_interns.pop_back();
            }
        }
    }

    return apartments_to_tenants;
}
/******************************************************************************************* */

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
using namespace std;

struct Apartment {
    int apt_id;       // Apartment ID
    int num_bedrooms; // Number of bedrooms
};

struct Person {
    string name;      // Intern's name
    bool wants_housemates; // Preference: true if they want to share
};

unordered_map<int, vector<string>> assignApartments(vector<Apartment>& apartments, vector<Person>& interns) {
    // Output map: Apartment ID -> List of intern names
    unordered_map<int, vector<string>> apartments_to_tenants;

    // Separate interns based on preferences
    vector<Person> sharing_interns, solo_interns;
    for (const auto& intern : interns) {
        if (intern.wants_housemates) {
            sharing_interns.push_back(intern);
        } else {
            solo_interns.push_back(intern);
        }
    }

    // Sort apartments by number of bedrooms (ascending)
    sort(apartments.begin(), apartments.end(), [](const Apartment& a, const Apartment& b) {
        return a.num_bedrooms < b.num_bedrooms;
    });

    // Allocate apartments
    size_t intern_index = 0;

    // Assign single-bedroom apartments to solo interns first
    for (auto& apartment : apartments) {
        if (apartment.num_bedrooms == 1 && !solo_interns.empty()) {
            apartments_to_tenants[apartment.apt_id].push_back(solo_interns.back().name);
            solo_interns.pop_back();
        }
    }

    // Assign multi-bedroom apartments to sharing interns
    for (auto& apartment : apartments) {
        if (apartment.num_bedrooms > 1 && !sharing_interns.empty()) {
            for (int i = 0; i < apartment.num_bedrooms && !sharing_interns.empty(); i++) {
                apartments_to_tenants[apartment.apt_id].push_back(sharing_interns.back().name);
                sharing_interns.pop_back();
            }
        }
    }

    // Assign remaining interns to any available apartments
    for (auto& apartment : apartments) {
        while (!solo_interns.empty() && apartments_to_tenants[apartment.apt_id].size() < apartment.num_bedrooms) {
            apartments_to_tenants[apartment.apt_id].push_back(solo_interns.back().name);
            solo_interns.pop_back();
        }
        while (!sharing_interns.empty() && apartments_to_tenants[apartment.apt_id].size() < apartment.num_bedrooms) {
            apartments_to_tenants[apartment.apt_id].push_back(sharing_interns.back().name);
            sharing_interns.pop_back();
        }
    }

    return apartments_to_tenants;
}


