#include <vector>
#include <iostream>

using namespace std;

bool all_sub_vector_emtpy(vector<vector<int>> &queues)
{
    for (auto elem : queues)
    {
        if (elem.size() > 0)
            return false;
    }
    return true;
}

int save_get(vector<vector<int>> queues, int floor, int default_value)
{
    if (floor >= queues.size() | floor < 0)
    {
        cout << "Floor is" << floor << " and queues hat only " << queues.size() << " floors. This can't be!" << endl;
        throw("Entered non-existing floor");
    }

    if (queues[floor].size() > 0)
        return queues[floor][0];
    else
        return default_value;
}

bool no_one_wants_in(bool up, int current_floor, vector<int> &people, vector<vector<int>> &queues)
{
    int first_person;
    if (up)
    {
        // Anyone it wants out above this floor.
        for (auto person : people)
        {
            if (person > current_floor)
            {
                return false;
            }
        }

        // Anyone above wants in
        for (int next_floor = current_floor + 1; next_floor < queues.size(); next_floor++)
        {
            if (next_floor >= save_get(queues, next_floor, next_floor - 1))
            {
                return false;
            }
        }
    }
    else
    {
        // Anyone it wants out above this floor.
        for (auto person : people)
        {
            if (person < current_floor)
            {
                return false;
            }
        }

        // Anyone above wants in
        for (int next_floor = current_floor - 1; next_floor >= 0; next_floor--)
        {
            if (next_floor <= save_get(queues, next_floor, next_floor - 1))
            {
                return false;
            }
        }
    }
    return true;
}

bool smart_turn(bool up, int current_floor, vector<vector<int>> queues)
{
    // The lift is empty. It only turns if it reached the highest / lowest person wanting in the opposite direction.
    if (up)
    {
        for (int next_floor = current_floor + 1; next_floor < queues.size(); next_floor++)
        {
            if (queues[next_floor].size() > 0)
            {
                if (queues[next_floor][0] < next_floor)
                {
                    return false;
                }
            }
        }
    }
    else
    {
        for (int next_floor = current_floor - 1; next_floor >= 0; next_floor--)
        {
            if (queues[next_floor].size() > 0)
            {
                if (queues[next_floor][0] > next_floor)
                {
                    return false;
                }
            }
        }
    }
    return true;
}

class Lift
{
private:
    bool up;
    int floor;
    int capacity;
    vector<int> people;
    int move();
    bool turns(vector<vector<int>> &queues);
    bool done(vector<vector<int>> &queues);

public:
    Lift(int);
    vector<int> process(vector<vector<int>>);
};

int Lift::move()
{
    if (this->up)
    {
        return this->floor + 1;
    }

    else
    {
        return this->floor - 1;
    }
}
bool Lift::turns(vector<vector<int>> &queues)
{
    //cout << "We are at floor" << this->floor << " and up is" << this->up << " and there are currenly " << this->people.size() << " people in the lift." << endl;
    // if still people in the elevator stay in direction.
    // Otherwise change direction if no one else needs to get off.
    if (this->people.size() != 0 && no_one_wants_in(this->up, this->floor, this->people, queues))
        return !this->up;

    if (this->people.size() == 0 && smart_turn(this->up, this->floor, queues))
    {
        return !this->up;
    }

    // if max or min floor is reached turn.
    if (this->up)
    {
        if (floor >= queues.size() - 1)
        {
            return false;
        }
        else
        {
            return true;
        }
    }
    else
    {
        if (floor <= 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    //cout << "Now up is " << this->up << "." << endl;
    cout << "this can't be!!" << endl;
}

bool Lift::done(vector<vector<int>> &queues)
{
    // Return true if the elevator is done.
    // Two conditions:
    // - Elevator empty.
    // - Each queue empty.
    return this->people.size() == 0 & all_sub_vector_emtpy(queues);
}
Lift::Lift(int capacity)
{
    this->capacity = capacity;
    this->floor = 0;
    this->up = true;
}

bool wants_in(bool up, int floor, int person)
{
    if (up)
    {
        if (floor < person)
        {
            return true;
        }
    }
    else
    {
        if (floor > person)
        {
            return true;
        }
    }
    return false;
}

vector<int> Lift::process(vector<vector<int>> queues)
{
    vector<int> output;
    output.push_back(0);

    // cout << "queues: {";
    // for (auto elem : queues)
    // {
    //     cout << "{";
    //     for (auto inner_elem : elem)
    //     {
    //         cout << inner_elem << ", ";
    //     }

    //     cout << "}, ";
    // }
    // cout << "}" << endl;

    // If there are people in the lowest floor, let them in!
    while (this->people.size() <= this->capacity & wants_in(this->up, this->floor, save_get(queues, this->floor, this->floor)))
    {
        this->people.push_back(queues[this->floor][0]);
        queues[this->floor].erase(queues[this->floor].begin());
    }

    while (!this->done(queues))
    {
        //cout << "this->floor: " << this->floor << " this->up: " << this->up << endl;
        // Will the elevator turn?
        this->up = this->turns(queues);

        // Move the elevator.
        this->floor = this->move();

        //cout << "After: this->floor: " << this->floor << " this->up: " << this->up << endl;

        // Let the people off if they match the current floor.
        bool rel_floor = false;
        auto cur_person = this->people.begin();
        while (cur_person != this->people.end())
        {
            if (*cur_person == this->floor)
            {
                cur_person = this->people.erase(cur_person);
                rel_floor = true;
            }
            else
            {
                cur_person++;
            }
        }

        // Let people in if they want in the current direction
        // and the capacity is not yet reached.
        while (this->people.size() <= this->capacity & wants_in(this->up, this->floor, save_get(queues, this->floor, this->floor)))
        {
            this->people.push_back(queues[this->floor][0]);
            queues[this->floor].erase(queues[this->floor].begin());
            rel_floor = true;
        }

        if (rel_floor)
        {
            output.push_back(this->floor);
        }
    }

    // If final floor is not zero, append it.
    if (output[output.size() - 1] != 0)
    {
        output.push_back(0);
    }
    return output;
}

vector<int> the_lift(vector<vector<int>> queues, int capacity)
{
    Lift this_lift = Lift(capacity);
    vector<int> floors = this_lift.process(queues);
    return floors;
}

bool compare_results(vector<int> expected_result, vector<int> result)
{
    bool failed = false;
    for (int idx = 0; idx < expected_result.size(); idx++)
    {
        if (idx >= result.size())
        {
            cout << "Results should have length " << expected_result.size() << " but are or length " << result.size() << endl;
            return true;
        }
        if (expected_result[idx] != result[idx])
        {
            cout << "Element " << idx << " should be " << expected_result[idx] << " but is " << result[idx] << "." << endl;
            failed = true;
        }
        return failed;
    }
}

bool run_test(vector<vector<int>> queues, vector<int> expected_result, int capacity = 5)
{

    vector<int> result = the_lift(queues, 5);
    bool failed = compare_results(expected_result, result);

    if (!failed)
    {
        cout << "Test succeeded!" << endl;
    }
    else
    {
        cout << "Test Failed! Result was: \n(";
        for (auto elem : result)
        {
            cout << elem << ", ";
        }
        cout << ")\nbut should be:\n(";
        for (auto elem : expected_result)
        {
            cout << elem << ", ";
        }
        cout << ")" << endl;
    }
}

int run_tests(vector<vector<vector<int>>> queues_per_test, vector<vector<int>> result_per_test)
{
    int failed_count = 0;
    for (int idx = 0; idx < queues_per_test.size(); idx++)
    {
        failed_count += run_test(queues_per_test[idx], result_per_test[idx], 5);
    }

    return failed_count;
}

int main()
{
    vector<vector<int>> queues;
    vector<int> result;
    vector<int> expected_result;

    run_tests({
                  {{}, {}, {5, 5, 5}, {}, {}, {}, {}},
                  //    {{}, {}, {1, 1}, {}, {}, {}, {}},
                  //    {{}, {3}, {4}, {}, {5}, {}, {}},
                  //    {{}, {0}, {}, {}, {2}, {3}, {}},
                  //    {
                  //        {3},
                  //        {2},
                  //        {0},
                  //        {2},
                  //        {},
                  //        {},
                  //        {5},
                  //    }

              },
              {//       {0, 2, 5, 0},
               //    {0, 2, 1, 0},
               //    {0, 1, 2, 3, 4, 5, 0},
               //    {0, 5, 4, 3, 2, 1, 0},
               {0, 1, 2, 3, 6, 5, 3, 2, 0}});

    // run_tests({{
    //               {3},
    //               {2},
    //               {0},
    //               {2},
    //               {},
    //               {},
    //               {5},
    //           }

    //           },
    //           {{0, 1, 2, 3, 6, 5, 3, 2, 0}});
}
