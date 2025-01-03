import math  # Importing the math library for trigonometric calculations

def clamp_angle(angle):
    """Clamp the angle to the servo's range of 0° to 180°"""
    return max(0, min(180, angle))

def inverse_kinematics(x, y, z, femur_length, tibia_length, coxa_length):
    # Calculate the horizontal distance from the base to the target
    distance = math.sqrt(x**2 + y**2)
    
    # Coxa angle (rotation in XY plane)
    theta_coxa = math.atan2(y, x)
    
    # Adjust distance for the femur-tibia plane
    adjusted_distance = distance - coxa_length

    # Distance from femur joint to target
    femur_to_target = math.sqrt(adjusted_distance**2 + z**2)

    # Check if target is reachable
    if femur_to_target > femur_length + tibia_length:
        raise ValueError("Target is out of reach")

    # Femur angle using the law of cosines
    alpha = math.atan2(z, adjusted_distance)  # Angle between horizontal and target
    beta = math.acos((femur_length**2 + femur_to_target**2 - tibia_length**2) /
                     (2 * femur_length * femur_to_target))  # Inner angle
    theta_femur = alpha + beta  # Total femur angle

    # Tibia angle using the law of cosines
    theta_tibia = math.acos((femur_length**2 + tibia_length**2 - femur_to_target**2) /
                            (2 * femur_length * tibia_length))  # Inner angle
    theta_tibia = math.pi - theta_tibia  # Adjust to correct orientation

    # Convert angles to degrees and clamp them to servo range
    return (
        clamp_angle(math.degrees(theta_coxa)), 
        clamp_angle(math.degrees(theta_femur)), 
        clamp_angle(math.degrees(theta_tibia))
    )

# Example usage
x = 100  # Target X position in mm
y = 50   # Target Y position in mm
z = -75  # Target Z position in mm
femur_length = 100  # Femur length in mm
tibia_length = 120  # Tibia length in mm
coxa_length = 50    # Coxa length in mm

angles = inverse_kinematics(x, y, z, femur_length, tibia_length, coxa_length)
print(f"Coxa Angle: {angles[0]}°\nFemur Angle: {angles[1]}°\nTibia Angle: {angles[2]}°")
