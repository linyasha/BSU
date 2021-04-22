package mainPackage;

import javax.swing.table.AbstractTableModel;

@SuppressWarnings("serial")
public class FunctionTableModel extends AbstractTableModel {
    private Double from, to, step, param;       // от, до, шаг, параметр
    public FunctionTableModel(Double from, Double to, Double step, Double param) {
        this.from = from;
        this.to = to;
        this.step = step;
        this.param = param;
    }

    public Double getFrom() { return from; }            //возвращает т к у нас все эти переменные private }

    public Double getTo() { return to; }

    public Double getStep() { return step; }

    public Double getParam(){ return param; }

    public int getColumnCount() { return 3; }

    public int getRowCount() {
        //Вычислить количество значений аргумента исходя из шага
        return new Double(Math.ceil((to-from)/step)).intValue()+1;
    }

    public Object getValueAt(int row, int col) {
        //Вычислить значение X (col=0) как НАЧАЛО_ОТРЕЗКА + ШАГ*НОМЕР_СТРОКИ
        double x = from + step*row;
        double y = param - x;

        switch (col) {
            case 0: return x;
            case 1: return y;
        }
        return y < 1 && y >= 0 || y > -1 && y < 0;
    }

    public String getColumnName(int col) {
        switch (col) {
            case 0: return "Value х";
            case 1: return "Value у";
            case 2: return "Integer part of Y is 0 ?";
        }
        return "";
    }

    public Class<?> getColumnClass(int col) {
        //И в 1-ом и во 2-ом столбце находятся значения типа Double
        if (col != 2) return Double.class;
        return Boolean.class;

    }
}
