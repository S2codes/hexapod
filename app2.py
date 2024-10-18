import tkinter as tk
from tkinter import ttk
import math
import matplotlib.pyplot as plt
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
from mpl_toolkits.mplot3d import Axes3D
import numpy as np

class HexapodMissionPlanner:
    def __init__(self, master):
        self.master = master
        master.title("Hexapod Mission Planner")
        master.geometry("1600x900")

        self.mission_steps = []
        self.current_step = 0
        self.is_executing = False
        self.pitch = 0
        self.roll = 0
        self.yaw = 0

        # Create main frames
        self.left_frame = ttk.Frame(master, padding="10")
        self.center_frame = ttk.Frame(master, padding="10")
        self.right_frame = ttk.Frame(master, padding="10")

        self.left_frame.grid(row=0, column=0, sticky="nsew")
        self.center_frame.grid(row=0, column=1, sticky="nsew")
        self.right_frame.grid(row=0, column=2, sticky="nsew")

        master.grid_columnconfigure(0, weight=1)
        master.grid_columnconfigure(1, weight=2)
        master.grid_columnconfigure(2, weight=1)
        master.grid_rowconfigure(0, weight=1)

        self.create_left_panel()
        self.create_center_panel()
        self.create_right_panel()

    def create_left_panel(self):
        ttk.Label(self.left_frame, text="Mission Planner", font=("Arial", 16, "bold")).pack(pady=10)

        # Mission grid
        self.grid_frame = ttk.Frame(self.left_frame)
        self.grid_frame.pack(pady=10)
        for i in range(5):
            for j in range(5):
                ttk.Frame(self.grid_frame, width=50, height=50, style="Grid.TFrame").grid(row=i, column=j, padx=2, pady=2)

        # Control buttons
        control_frame = ttk.Frame(self.left_frame)
        control_frame.pack(pady=10)
        ttk.Button(control_frame, text="Forward", command=lambda: self.add_step("Move Forward")).grid(row=0, column=1, padx=5, pady=5)
        ttk.Button(control_frame, text="Backward", command=lambda: self.add_step("Move Backward")).grid(row=2, column=1, padx=5, pady=5)
        ttk.Button(control_frame, text="Left", command=lambda: self.add_step("Turn Left")).grid(row=1, column=0, padx=5, pady=5)
        ttk.Button(control_frame, text="Right", command=lambda: self.add_step("Turn Right")).grid(row=1, column=2, padx=5, pady=5)

        # Mission steps list
        ttk.Label(self.left_frame, text="Mission Steps", font=("Arial", 12, "bold")).pack(pady=10)
        self.steps_listbox = tk.Listbox(self.left_frame, height=10, width=30)
        self.steps_listbox.pack(pady=5)

    def create_center_panel(self):
        ttk.Label(self.center_frame, text="Camera View", font=("Arial", 16, "bold")).pack(pady=10)

        # Camera view (placeholder)
        self.camera_frame = ttk.Frame(self.center_frame, width=400, height=300, style="Camera.TFrame")
        self.camera_frame.pack(pady=10)
        ttk.Label(self.camera_frame, text="Camera Feed", style="Camera.TLabel").place(relx=0.5, rely=0.5, anchor="center")

        # Manual control buttons
        control_frame = ttk.Frame(self.center_frame)
        control_frame.pack(pady=10)
        ttk.Button(control_frame, text="↺", command=lambda: self.control("rotateLeft")).grid(row=0, column=0, padx=5, pady=5)
        ttk.Button(control_frame, text="Forward", command=lambda: self.control("forward")).grid(row=0, column=1, padx=5, pady=5)
        ttk.Button(control_frame, text="↻", command=lambda: self.control("rotateRight")).grid(row=0, column=2, padx=5, pady=5)
        ttk.Button(control_frame, text="Left", command=lambda: self.control("left")).grid(row=1, column=0, padx=5, pady=5)
        ttk.Button(control_frame, text="Backward", command=lambda: self.control("backward")).grid(row=1, column=1, padx=5, pady=5)
        ttk.Button(control_frame, text="Right", command=lambda: self.control("right")).grid(row=1, column=2, padx=5, pady=5)

        # 3D Gyroscopic view
        ttk.Label(self.center_frame, text="3D Gyroscopic View", font=("Arial", 12, "bold")).pack(pady=10)
        self.fig = plt.Figure(figsize=(5, 5), dpi=100)
        self.ax = self.fig.add_subplot(111, projection='3d')
        self.canvas = FigureCanvasTkAgg(self.fig, master=self.center_frame)
        self.canvas.draw()
        self.canvas.get_tk_widget().pack(side=tk.TOP, fill=tk.BOTH, expand=1)
        self.update_3d_gyro()

    def create_right_panel(self):
        ttk.Label(self.right_frame, text="Mission Execution", font=("Arial", 16, "bold")).pack(pady=10)

        # Execution buttons
        exec_frame = ttk.Frame(self.right_frame)
        exec_frame.pack(pady=10)
        ttk.Button(exec_frame, text="Start", command=self.execute_mission).grid(row=0, column=0, padx=5, pady=5)
        ttk.Button(exec_frame, text="Pause", command=self.pause_mission).grid(row=0, column=1, padx=5, pady=5)
        ttk.Button(exec_frame, text="Stop", command=self.stop_mission).grid(row=0, column=2, padx=5, pady=5)

        # Speed control
        ttk.Label(self.right_frame, text="Speed Control", font=("Arial", 12, "bold")).pack(pady=10)
        self.speed_scale = ttk.Scale(self.right_frame, from_=0, to=100, orient="horizontal", length=200)
        self.speed_scale.set(50)
        self.speed_scale.pack()
        ttk.Label(self.right_frame, text="Slow").place(x=50, y=220)
        ttk.Label(self.right_frame, text="Fast").place(x=250, y=220)

        # Status display
        ttk.Label(self.right_frame, text="Status", font=("Arial", 12, "bold")).pack(pady=20)
        self.status_text = tk.Text(self.right_frame, height=6, width=30, state="disabled")
        self.status_text.pack()
        self.update_status()

        # Orientation control (for demonstration purposes)
        ttk.Label(self.right_frame, text="Orientation Control (Demo)", font=("Arial", 12, "bold")).pack(pady=10)
        
        pitch_frame = ttk.Frame(self.right_frame)
        pitch_frame.pack(pady=5)
        ttk.Label(pitch_frame, text="Pitch:").pack(side="left")
        self.pitch_scale = ttk.Scale(pitch_frame, from_=-90, to=90, orient="horizontal", length=200, command=self.update_orientation)
        self.pitch_scale.pack(side="left")

        roll_frame = ttk.Frame(self.right_frame)
        roll_frame.pack(pady=5)
        ttk.Label(roll_frame, text="Roll:  ").pack(side="left")
        self.roll_scale = ttk.Scale(roll_frame, from_=-90, to=90, orient="horizontal", length=200, command=self.update_orientation)
        self.roll_scale.pack(side="left")

        yaw_frame = ttk.Frame(self.right_frame)
        yaw_frame.pack(pady=5)
        ttk.Label(yaw_frame, text="Yaw:  ").pack(side="left")
        self.yaw_scale = ttk.Scale(yaw_frame, from_=-180, to=180, orient="horizontal", length=200, command=self.update_orientation)
        self.yaw_scale.pack(side="left")

    def add_step(self, step):
        self.mission_steps.append(step)
        self.steps_listbox.insert(tk.END, step)

    def execute_mission(self):
        self.is_executing = True
        self.current_step = 0
        self.update_mission_display()
        print("Executing mission")  # In a real app, you'd send commands to the robot here

    def pause_mission(self):
        self.is_executing = False
        self.update_mission_display()
        print("Mission paused")  # In a real app, you'd pause the robot's movement here

    def stop_mission(self):
        self.is_executing = False
        self.current_step = 0
        self.update_mission_display()
        print("Mission stopped")  # In a real app, you'd stop the robot and reset its position here

    def control(self, direction):
        print(f"Manual control: {direction}")  # In a real app, you'd send control commands to the robot here

    def update_mission_display(self):
        self.steps_listbox.selection_clear(0, tk.END)
        if self.is_executing and self.mission_steps:
            self.steps_listbox.selection_set(self.current_step)
            self.steps_listbox.see(self.current_step)

    def update_status(self):
        status = f"Battery: 75%\nSignal Strength: Good\nCurrent Position: X: 10, Y: 15\nOrientation:\n  Pitch: {self.pitch:.1f}°\n  Roll: {self.roll:.1f}°\n  Yaw: {self.yaw:.1f}°"
        self.status_text.config(state="normal")
        self.status_text.delete(1.0, tk.END)
        self.status_text.insert(tk.END, status)
        self.status_text.config(state="disabled")
        self.master.after(100, self.update_status)  # Update every 100ms

    def update_3d_gyro(self):
        self.ax.clear()
        self.ax.set_xlim([-1, 1])
        self.ax.set_ylim([-1, 1])
        self.ax.set_zlim([-1, 1])
        self.ax.set_xlabel('X')
        self.ax.set_ylabel('Y')
        self.ax.set_zlabel('Z')

        # Create a cube
        r = [-1, 1]
        x, y = np.meshgrid(r, r)
        one = np.ones(4).reshape(2, 2)
        z = one * -1
        self.ax.plot_surface(x, y, z, alpha=0.5)
        z = one * 1
        self.ax.plot_surface(x, y, z, alpha=0.5)
        self.ax.plot_surface(x, z, y, alpha=0.5)
        self.ax.plot_surface(x, z, -y, alpha=0.5)
        self.ax.plot_surface(z, x, y, alpha=0.5)
        self.ax.plot_surface(-z, x, y, alpha=0.5)

        # Rotate the cube
        self.ax.view_init(self.pitch, self.yaw)
        self.fig.canvas.draw_idle()

    def update_orientation(self, _):
        self.pitch = self.pitch_scale.get()
        self.roll = self.roll_scale.get()
        self.yaw = self.yaw_scale.get()
        self.update_3d_gyro()

if __name__ == "__main__":
    root = tk.Tk()
    app = HexapodMissionPlanner(root)
    
    # Configure styles
    style = ttk.Style()
    style.configure("Grid.TFrame", background="lightgray")
    style.configure("Camera.TFrame", background="black")
    style.configure("Camera.TLabel", background="black", foreground="white", font=("Arial", 14))
    
    root.mainloop()