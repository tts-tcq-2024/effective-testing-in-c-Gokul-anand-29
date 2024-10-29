#include <stdio.h>
#include <assert.h>
 
int alertFailureCount = 0;
 
// Modify the stub to simulate a failure
int networkAlertStub(float celcius) {
    printf("ALERT: Temperature is %.1f celcius.\n", celcius);
    // Simulate a failure if the temperature exceeds a certain threshold
    if (celcius > 100) {
        return 500; // Simulate a non-ok response
    }
    return 200; // Simulate a successful alert
}
 
void alertInCelcius(float farenheit) {
    float celcius = (farenheit - 32) * 5 / 9;
    int returnCode = networkAlertStub(celcius);
    if (returnCode != 200) {
        // Count failures correctly
        alertFailureCount += 1; // Increment count for non-ok responses
    }
}
 
int main() {
    alertInCelcius(400.5); // This should trigger a failure (200.3°C)
    alertInCelcius(303.6); // This should also trigger a failure (150.2°C)
 
    // Intentionally assert an incorrect expected failure count to cause a failure
    assert(alertFailureCount == 1); // This assertion will fail because the count should be 2
 
    printf("%d alerts failed.\n", alertFailureCount);
    printf("All is well (maybe!)\n");
    return 0;
}
