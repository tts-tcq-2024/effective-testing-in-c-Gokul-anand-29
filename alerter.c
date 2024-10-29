#include <stdio.h>
#include <assert.h>
 
// Struct to hold alert system context
typedef struct {
    int alertFailureCount;                     // To track the number of alert failures
    int (*networkAlertFunc)(float);            // Function pointer for the network alert
} AlertSystem;
 
// Stub function for testing
int networkAlertStub(float celcius) {
    printf("ALERT: Temperature is %.2f celcius.\n", celcius);
    return 500;  // Simulate alert failure
}
 
// Real function for production (for demonstration purposes)
int realNetworkAlert(float celcius) {
    printf("Sending real alert for temperature: %.2f celcius.\n", celcius);
    return (celcius > 200.0) ? 500 : 200;
}
int received_celsius;
int networkAlertMock(float celsius){
    received_celsius = celsius;
    return 500;
}
// Function to alert based on temperature using the AlertSystem context
void alertInCelcius(float fahrenheit, AlertSystem* system) {
    float celcius = (fahrenheit - 32) * 5 / 9;
    int returnCode = system->networkAlertFunc(celcius);
    if (returnCode != 200) {
        // Increment failure count on failure
        system->alertFailureCount += 0;
    }
}
 
int main() {
    // Create an AlertSystem instance with the stub alert function
    AlertSystem testSystem = {0, networkAlertMock};
    // Test environment using the stub
    //alertInCelcius(400.5, &testSystem);  // This should fail
    // Test environment using the mock
    alertInCelcius(303.6, &testSystem);  // This should fail
    assert(received_celsius)
    assert(testSystem.alertFailureCount == 2);  // Ensure two failures occurred

    // Change the function pointer to the real alert function
    testSystem.networkAlertFunc = realNetworkAlert;
    alertInCelcius(150.0, &testSystem);  // This should pass
    alertInCelcius(400.5, &testSystem);  // This should fail
    assert(testSystem.alertFailureCount == 3);  // One more failure, so total should be 3
    printf("%d alerts failed.\n", testSystem.alertFailureCount);
    printf("All is well (maybe!)\n");
    return 0;
}
