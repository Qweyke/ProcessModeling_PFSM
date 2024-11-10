#include <iostream>
#include <string>
namespace
{
constexpr uint16_t STATES         = 2;
constexpr uint16_t INPUT_SIGNALS  = 3;
constexpr uint16_t OUTPUT_SIGNALS = 3;

constexpr uint32_t OUTPUT_PROBABILITES = STATES * INPUT_SIGNALS;

// input signals display
constexpr const char* INP_REQ = "(HTTP request)";
constexpr const char* INP_ERR = "(Server. Error signal)";
constexpr const char* INP_SUC = "(Server. Success signal)";

// states display
constexpr const char* ST_WAIT = "{Waiting for request}";
constexpr const char* ST_WORK = "{Working with request}";

// output signals display
constexpr const char* OUT_DONE = "[HTTP. Done]";
constexpr const char* OUT_ERR  = "[HTTP. Error]";
constexpr const char* OUT_HAND = "[HTTP. Handling]";

enum States
{
    WAIT,
    WORK
};
}

std::uint32_t outputSignalsProbabilities[OUTPUT_PROBABILITES][OUTPUT_PROBABILITES] = {
    { 0, 10, 0, 0, 10, 80 }, { 0, 5, 0, 30, 5, 60 }, { 0, 100, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 100, 0 },  { 0, 100, 0, 0, 0, 0 }, { 95, 5, 0, 0, 0, 0 },
};

uint32_t    states[STATES]    = { WAIT, WORK };
std::string stateText[STATES] = { ST_WAIT, ST_WORK };

std::string inputSignals[INPUT_SIGNALS]   = { INP_REQ, INP_ERR, INP_SUC };
std::string outputSignals[OUTPUT_SIGNALS] = { OUT_DONE, OUT_ERR, OUT_HAND };

uint32_t static calculateProbability(uint16_t inSignal, uint16_t currState)
{
    const uint16_t start = 0;
    const uint16_t end   = 100;

    uint32_t newState;
    bool     init = false;

    const uint32_t outputProbability = rand() % (end - start) + 1;
    const uint32_t outputRow         = currState + (inSignal * STATES);

    uint32_t probSum = 0;
    for (int outputColumn = 0; outputColumn < (OUTPUT_PROBABILITES); outputColumn++)
    {
        probSum += outputSignalsProbabilities[outputRow][outputColumn];

        if (probSum >= outputProbability)
        {
            probSum  = 0;
            newState = outputColumn / OUTPUT_SIGNALS;
            init     = true;
            std::cout << outputSignals[outputColumn % OUTPUT_SIGNALS] << " with "
                      << outputSignalsProbabilities[outputRow][outputColumn]
                      << "% probability, row: " << outputRow << std::endl;
            break;
        }
    }

    if (init)
        return newState;

    else
        throw std::runtime_error("No state initialized!");
}

void static displaySignals(std::string signals[], size_t size)
{
    std::string output;
    output.reserve(size * 40);
    std::cout << "Input signals:\n";

    int i = 0;
    for (i; i < size; i++)
    {
        output += std::to_string(i) + " - " + (signals[i]) + (";\n");
    }

    output += (std::to_string(i)) + " - Show hint;\n" + (std::to_string(i + 1))
              + " - Exit program. \n\n";
    std::cout << output;
}

void static displayState(uint16_t state)
{
    std::cout << "Current state: " << state << " - " << stateText[state] << "\n\n";
}


int main()
{
    uint16_t currentState = 0;
    uint16_t inSignal     = 0;

    displayState(currentState);
    displaySignals(inputSignals, INPUT_SIGNALS);

    srand(time(0));

    while (1)
    {
        std::cout << "Signal:";
        std::cin >> inSignal;
        std::cout << "\n";
        if ((inSignal < INPUT_SIGNALS) && (inSignal >= 0))
        {
            currentState = calculateProbability(inSignal, currentState);
            displayState(currentState);
        }
        else if (inSignal == INPUT_SIGNALS)
        {
            displaySignals(inputSignals, INPUT_SIGNALS);
        }

        else if (inSignal == INPUT_SIGNALS + 1)
        {
            std::cout << "Exiting program \n\n";
            break;
        }

        else
        {
            std::cout << "Unknown input signal \n\n";
        }
    }
    return 0;
}