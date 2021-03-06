//--------------------------------------------------------------------------------------------------
/**
 * Periodic sensor scaffold.  Used to implement generic periodic sensors.
 *
 * Copyright (C) Sierra Wireless Inc.
 */
//--------------------------------------------------------------------------------------------------

#ifndef PERIODIC_SENSOR_H_INCLUDE_GUARD
#define PERIODIC_SENSOR_H_INCLUDE_GUARD


//--------------------------------------------------------------------------------------------------
/**
 * Maximum number of bytes in a sensor name (including null terminator).
 */
//--------------------------------------------------------------------------------------------------
#define PSENSOR_MAX_NAME_BYTES  32


//--------------------------------------------------------------------------------------------------
/**
 * Reference to a periodic sensor scaffold.
 */
//--------------------------------------------------------------------------------------------------
typedef struct psensor* psensor_Ref_t;


//--------------------------------------------------------------------------------------------------
/**
 * Creates a periodic sensor scaffold for a sensor with a given name.
 *
 * This makes the sensor appear in the Data Hub and creates a timer for that sensor.
 * The sampleFunc will be called whenever it's time to take a sample.  The sampleFunc must
 * call one of the psensor_PushX() functions below.
 *
 * @return Reference to the new periodic sensor scaffold.
 */
//--------------------------------------------------------------------------------------------------
LE_SHARED psensor_Ref_t psensor_Create
(
    const char* name,   ///< Name of the periodic sensor.
    dhubIO_DataType_t dataType,
    const char* units,
    void (*sampleFunc)(psensor_Ref_t ref) ///< Sample function to be called back periodically.
);


//--------------------------------------------------------------------------------------------------
/**
 * Push a boolean sample to the Data Hub.
 */
//--------------------------------------------------------------------------------------------------
LE_SHARED void psensor_PushBoolean
(
    psensor_Ref_t ref,  ///< Reference returned by psensor_Create().
    double timestamp,   ///< Timestamp (or 0 = now).
    bool value
);


//--------------------------------------------------------------------------------------------------
/**
 * Push a numeric sample to the Data Hub.
 */
//--------------------------------------------------------------------------------------------------
LE_SHARED void psensor_PushNumeric
(
    psensor_Ref_t ref,  ///< Reference returned by psensor_Create().
    double timestamp,   ///< Timestamp (or 0 = now).
    double value
);


//--------------------------------------------------------------------------------------------------
/**
 * Push a string sample to the Data Hub.
 */
//--------------------------------------------------------------------------------------------------
LE_SHARED void psensor_PushString
(
    psensor_Ref_t ref,  ///< Reference returned by psensor_Create().
    double timestamp,   ///< Timestamp (or 0 = now).
    const char* value
);


//--------------------------------------------------------------------------------------------------
/**
 * Push a JSON sample to the Data Hub.
 */
//--------------------------------------------------------------------------------------------------
LE_SHARED void psensor_PushJson
(
    psensor_Ref_t ref,  ///< Reference returned by psensor_Create().
    double timestamp,   ///< Timestamp (or 0 = now).
    const char* value
);


#endif // PERIODIC_SENSOR_H_INCLUDE_GUARD
