import math

# home position in encoder ticks for the servo.

servo_param = {
    1: {                        # Default for new servo.  Please issue 'new_servo.write_id(new_id)' and setup your own home position!
        'home_encoder': 351
       }, 
    2: {                        # Shoulder 2
        'home_encoder': 140,
        'max_ang': math.radians(360.),
        'min_ang': math.radians(-10.),
        'max_encoder' : 4095,
        'rad_per_enc' : math.radians(251.)/4095.
       }, 
    3: {                        # elbow1
        'home_encoder': 170,
        'max_ang': math.radians(360.),
        'min_ang': math.radians(-10.),
        'max_encoder' : 4095,
        'rad_per_enc' : math.radians(360.)/4095.
       },
    4: {                        # elbow2
        'home_encoder': 274,
        'max_ang': math.radians(360.),
        'min_ang': math.radians(-10.),
        'max_encoder' : 4095,
        'rad_per_enc' : math.radians(360.)/4095.
       },
    5: {                        # Wrist
        'home_encoder': 1340,
        'max_ang': math.radians(360.),
        'min_ang': math.radians(-360.),
        'max_encoder' : 4095,
        'rad_per_enc' : math.radians(360.)/4095.
       },
    6: {                        # End Effector
        'home_encoder': 0,
        'max_ang': math.radians(360.),
        'min_ang': math.radians(-10.),
        'max_encoder' : 4095,
        'rad_per_enc' : math.radians(360.)/4095.
       },
    7: {                        # Shoulder 1
        'home_encoder': 201,
        'max_ang': math.radians(360.),
        'min_ang': math.radians(-10.),
        'max_encoder' : 4095,
        'rad_per_enc' : math.radians(251.)/4095.  
        }
}

