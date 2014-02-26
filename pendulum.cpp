#include "Simbody.h"
using namespace SimTK;

int main() {
    // Define the system.
    MultibodySystem sys;
    SimbodyMatterSubsystem matter(sys);
    GeneralForceSubsystem forces(sys);
    Force::UniformGravity gravity(forces, matter, Vec3(0, -9.8, 0));

    // Describe mass and visualization properties for a generic body.
    Body::Rigid pendBody(MassProperties(1.0, Vec3(0), Inertia(1)));
    pendBody.addDecoration(Transform(), DecorativeSphere(0.1));

    // Create the moving (mobilized) bodies of the pendulum.
    MobilizedBody::Pin pend1(matter.Ground(), Transform(Vec3(0)),
            pendBody, Transform(Vec3(0, 1, 0)));
    MobilizedBody::Pin pend2(pend1, Transform(Vec3(0)),
            pendBody, Transform(Vec3(0, 1, 0)));

    // Set up visualization.
    Visualizer viz(sys);
    sys.addEventReporter(new Visualizer::Reporter(viz, 0.01));

    // Initialize the system and state.
    sys.realizeTopology();
    State state = sys.getDefaultState();
    pend2.setRate(state, 5.0);

    // Simulate for 50 seconds.
    RungeKuttaMersonIntegrator integ(sys);
    TimeStepper ts(sys, integ);
    ts.initialize(state);
    ts.stepTo(50.0);
}
