package com.newton449.virtualserverclient.testserver;

import com.newton449.virtualserverclient.installer.client.model.FileKeyModel;
import com.newton449.virtualserverclient.installer.client.model.FileUrlModel;
import java.io.IOException;
import java.io.PrintWriter;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

/**
 * It accepts a {@link FileKeyModel} which presents the requested file, and
 * replies a {@link FileUrlModel} which contains the file URL (if it is created)
 * or the creating process (if it is creating).
 *
 * @author Steven
 */
public class InstallerGetUrlServlet extends HttpServlet {

    private static int COUNT = 0;

    /**
     * Processes requests for both HTTP <code>GET</code> and <code>POST</code>
     * methods.
     *
     * @param request servlet request
     * @param response servlet response
     * @throws ServletException if a servlet-specific error occurs
     * @throws IOException if an I/O error occurs
     */
    protected void processRequest(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        response.setContentType("text/html;charset=UTF-8");
        try (PrintWriter out = response.getWriter()) {
            if (COUNT >= 9) {
                // finished
                out.print(buildResult("/_file/VirtualServer-all.zip", 500436, 100, 0));
                if (COUNT == 10) {
                    COUNT = 0;
                }
            } else {
                // processing
                out.print(buildResult(null, 0, COUNT * 10, 2000));
            }
            COUNT++;
        }
    }

    private String buildResult(String url, int size, float percentage, int waiting) {
        String ret = "{\n"
                + "    \"fileUrl\": " + (url == null ? "null" : '\"' + url + '\"') + ",\n"
                + "    \"fileSize\": " + size + ",\n"
                + "    \"percentage\": " + percentage + ",\n"
                + "    \"waitingMillisecond\": " + waiting + "\n"
                + "}";
        return ret;
    }

    // <editor-fold defaultstate="collapsed" desc="HttpServlet methods. Click on the + sign on the left to edit the code.">
    /**
     * Handles the HTTP <code>GET</code> method.
     *
     * @param request servlet request
     * @param response servlet response
     * @throws ServletException if a servlet-specific error occurs
     * @throws IOException if an I/O error occurs
     */
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        processRequest(request, response);
    }

    /**
     * Handles the HTTP <code>POST</code> method.
     *
     * @param request servlet request
     * @param response servlet response
     * @throws ServletException if a servlet-specific error occurs
     * @throws IOException if an I/O error occurs
     */
    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        processRequest(request, response);
    }

    /**
     * Returns a short description of the servlet.
     *
     * @return a String containing servlet description
     */
    @Override
    public String getServletInfo() {
        return "Short description";
    }// </editor-fold>

}
