#define GpsData 1


#ifdef GpsData
    #define GpsDataPrint(X) Serial.println(X)
#else
    #define GpsDataPrint(X)
#endif

#ifdef MainDebug
    #define MainDebugPrint(X) Serial.println(X)
#else
    #define MainDebugPrint(X)
#endif

Serial.p