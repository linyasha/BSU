import java.awt.*;
import javax.swing.*;

public class MainFrame extends JFrame {

    private static final int WIDTH = 400;
    private static final int HEIGHT = 300;

    public MainFrame() {
        super("Calculating function values");
        setSize(WIDTH, HEIGHT);

        Toolkit kit = Toolkit.getDefaultToolkit();
        setLocation((kit.getScreenSize().width - WIDTH) / 2,
                (kit.getScreenSize().height - HEIGHT) / 2);
        //центрирование окна по центру экрана


        JTextField textFieldP = new JTextField("0.0", 5);
        textFieldP.setHorizontalAlignment(JTextField.CENTER);
        textFieldP.setMaximumSize(new Dimension(2 * textFieldP.getPreferredSize().width,
                textFieldP.getPreferredSize().height));


        JLabel textFormula = new JLabel("Formula: f(x) = <Y = P - X>");
        textFormula.setAlignmentX(CENTER_ALIGNMENT);

        //_______________________________________________________________________
        JButton buttonMinus = new JButton("-");
        buttonMinus.addActionListener(e -> {
            try {
                double P = Double.parseDouble(textFieldP.getText());
                textFieldP.setText(Double.toString(P - 1));

            }
            catch (NumberFormatException error) {
                JOptionPane.showMessageDialog(null, error.getMessage(),
                        "Error!!", JOptionPane.ERROR_MESSAGE);
            }
        });


        JButton buttonPlus = new JButton("+");
        buttonPlus.addActionListener(e -> {
            try {
                double P = Double.parseDouble(textFieldP.getText());
                textFieldP.setText(Double.toString(P + 1));

            }
            catch (NumberFormatException error) {
                JOptionPane.showMessageDialog(null, error.getMessage(),
                        "Error!!", JOptionPane.ERROR_MESSAGE);
            }
        });
        // Function parameters
        //___________________________________________________________________________

        Box plusAndMunis = Box.createHorizontalBox();
        plusAndMunis.add(Box.createHorizontalGlue());
        plusAndMunis.add(buttonMinus);
        plusAndMunis.add(Box.createHorizontalStrut(10));
        plusAndMunis.add(buttonPlus);
        plusAndMunis.add(Box.createHorizontalGlue());


        Box hContainerP = Box.createHorizontalBox();
        hContainerP.add(Box.createHorizontalGlue());
        hContainerP.add(new JLabel("P:"));
        hContainerP.add(Box.createHorizontalStrut(20));
        hContainerP.add(textFieldP);
        hContainerP.add(Box.createHorizontalStrut(10));
        //hContainerP.add(buttonMinus);
        hContainerP.add(Box.createHorizontalStrut(10));
        //hContainerP.add(buttonPlus);
        hContainerP.add(Box.createHorizontalGlue());
        //hContainerP.setMaximumSize(new Dimension(hContainerP.getMaximumSize().width, hContainerP.getPreferredSize().height));  // зачем это


        Box vBoxP = Box.createVerticalBox();
        vBoxP.setBorder(BorderFactory.createTitledBorder(BorderFactory.createEtchedBorder(),
                "Function parameters:"));
        vBoxP.add(Box.createVerticalStrut(10));
        vBoxP.add(Box.createVerticalGlue());
        vBoxP.add(plusAndMunis);

        vBoxP.add(Box.createVerticalStrut(10));
        vBoxP.add(hContainerP);
        vBoxP.add(Box.createVerticalStrut(5));
        vBoxP.add(textFormula);
        vBoxP.add(Box.createVerticalGlue());
        vBoxP.setMaximumSize((new Dimension(vBoxP.getMaximumSize().width, 100)));
        getContentPane().add(vBoxP);

        vBoxP.add(Box.createVerticalStrut(10));


        // -------------------------------------------------------------------------------------------------------------


        JTextField textFieldX = new JTextField("0.0", 5);
        textFieldX.setHorizontalAlignment(JTextField.CENTER);
        textFieldX.setMaximumSize(new Dimension(2 * textFieldX.getPreferredSize().width,
                textFieldX.getPreferredSize().height));

        Box hContainerX = Box.createHorizontalBox();
        hContainerX.add(Box.createHorizontalGlue());
        hContainerX.add(new JLabel("X:"));
        hContainerX.add(Box.createHorizontalStrut(10));
        hContainerX.add(textFieldX);
        hContainerX.add(Box.createHorizontalGlue());
        hContainerX.setMaximumSize(new Dimension(hContainerX.getMaximumSize().width, hContainerX.getPreferredSize().height));


        JLabel labelY = new JLabel("");
        labelY.setHorizontalAlignment(JLabel.CENTER);
        labelY.setMinimumSize(textFieldX.getMaximumSize());
        labelY.setPreferredSize(textFieldX.getPreferredSize());


        //Calculation of values
        //_________________________________________________________________________

        Box hContainerY = Box.createHorizontalBox();
        hContainerY.add(Box.createHorizontalGlue());
        hContainerY.add(new JLabel("Y:"));
        hContainerY.add(Box.createHorizontalStrut(10));
        hContainerY.add(labelY);
        hContainerY.add(Box.createHorizontalGlue());
        hContainerY.setMaximumSize(new Dimension(hContainerY.getMaximumSize().width, hContainerY.getPreferredSize().height));


        JButton buttonCalculator = new JButton("Вычислить");
        buttonCalculator.setAlignmentX(CENTER_ALIGNMENT);
        buttonCalculator.addActionListener(ev -> {  //
            try {
                double X = Double.parseDouble(textFieldX.getText());
                double P = Double.parseDouble(textFieldP.getText());
                labelY.setText(Double.toString(P - X));
            } catch (NumberFormatException e) {
                JOptionPane.showMessageDialog(null, e.getMessage(),
                        "Error!!", JOptionPane.ERROR_MESSAGE);
            }
        });


        Box vboxCalculator = Box.createVerticalBox();
        vboxCalculator.setBorder(BorderFactory.createTitledBorder(BorderFactory.createEtchedBorder(),
                "Calculating the value of a function"));
        vboxCalculator.add(Box.createVerticalGlue());
        vboxCalculator.add(hContainerX);
        vboxCalculator.add(Box.createVerticalStrut(10));
        vboxCalculator.add(hContainerY);
        vboxCalculator.add(Box.createVerticalStrut(20));
        vboxCalculator.add(buttonCalculator);
        vboxCalculator.add(Box.createVerticalGlue());
        getContentPane().add(vboxCalculator);


        // -------------------------------------------------------------------------------------------------------------
        this.setLayout(new BoxLayout(this.getContentPane(), BoxLayout.Y_AXIS));

        }


    public static void main(String[] args) {
        MainFrame frame = new MainFrame();
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setVisible(true);
    }
}
